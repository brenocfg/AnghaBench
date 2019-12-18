#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct file {struct dmxdev_filter* private_data; } ;
struct dmxdev_filter {int /*<<< orphan*/  mutex; int /*<<< orphan*/  vb2_ctx; int /*<<< orphan*/  state; struct dmxdev* dev; } ;
struct dmxdev {int /*<<< orphan*/  mutex; TYPE_1__* demux; } ;
struct dmx_stc {int /*<<< orphan*/  base; int /*<<< orphan*/  stc; int /*<<< orphan*/  num; } ;
struct TYPE_3__ {int (* get_stc ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_pes_pids ) (TYPE_1__*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMXDEV_STATE_SET ; 
#define  DMX_ADD_PID 141 
#define  DMX_DQBUF 140 
#define  DMX_EXPBUF 139 
#define  DMX_GET_PES_PIDS 138 
#define  DMX_GET_STC 137 
#define  DMX_QBUF 136 
#define  DMX_QUERYBUF 135 
#define  DMX_REMOVE_PID 134 
#define  DMX_REQBUFS 133 
#define  DMX_SET_BUFFER_SIZE 132 
#define  DMX_SET_FILTER 131 
#define  DMX_SET_PES_FILTER 130 
#define  DMX_START 129 
#define  DMX_STOP 128 
 int EINVAL ; 
 int ENOTTY ; 
 int ERESTARTSYS ; 
 int dvb_dmxdev_add_pid (struct dmxdev*,struct dmxdev_filter*,int /*<<< orphan*/ ) ; 
 int dvb_dmxdev_filter_set (struct dmxdev*,struct dmxdev_filter*,void*) ; 
 int dvb_dmxdev_filter_start (struct dmxdev_filter*) ; 
 int dvb_dmxdev_filter_stop (struct dmxdev_filter*) ; 
 int dvb_dmxdev_pes_filter_set (struct dmxdev*,struct dmxdev_filter*,void*) ; 
 int dvb_dmxdev_remove_pid (struct dmxdev*,struct dmxdev_filter*,int /*<<< orphan*/ ) ; 
 int dvb_dmxdev_set_buffer_size (struct dmxdev_filter*,unsigned long) ; 
 int dvb_vb2_dqbuf (int /*<<< orphan*/ *,void*) ; 
 int dvb_vb2_expbuf (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dvb_vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int dvb_vb2_qbuf (int /*<<< orphan*/ *,void*) ; 
 int dvb_vb2_querybuf (int /*<<< orphan*/ *,void*) ; 
 int dvb_vb2_reqbufs (int /*<<< orphan*/ *,void*) ; 
 int dvb_vb2_stream_on (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_demux_do_ioctl(struct file *file,
			      unsigned int cmd, void *parg)
{
	struct dmxdev_filter *dmxdevfilter = file->private_data;
	struct dmxdev *dmxdev = dmxdevfilter->dev;
	unsigned long arg = (unsigned long)parg;
	int ret = 0;

	if (mutex_lock_interruptible(&dmxdev->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case DMX_START:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		if (dmxdevfilter->state < DMXDEV_STATE_SET)
			ret = -EINVAL;
		else
			ret = dvb_dmxdev_filter_start(dmxdevfilter);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_STOP:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_dmxdev_filter_stop(dmxdevfilter);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_SET_FILTER:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_dmxdev_filter_set(dmxdev, dmxdevfilter, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_SET_PES_FILTER:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_dmxdev_pes_filter_set(dmxdev, dmxdevfilter, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_SET_BUFFER_SIZE:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_dmxdev_set_buffer_size(dmxdevfilter, arg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_GET_PES_PIDS:
		if (!dmxdev->demux->get_pes_pids) {
			ret = -EINVAL;
			break;
		}
		dmxdev->demux->get_pes_pids(dmxdev->demux, parg);
		break;

	case DMX_GET_STC:
		if (!dmxdev->demux->get_stc) {
			ret = -EINVAL;
			break;
		}
		ret = dmxdev->demux->get_stc(dmxdev->demux,
					     ((struct dmx_stc *)parg)->num,
					     &((struct dmx_stc *)parg)->stc,
					     &((struct dmx_stc *)parg)->base);
		break;

	case DMX_ADD_PID:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			ret = -ERESTARTSYS;
			break;
		}
		ret = dvb_dmxdev_add_pid(dmxdev, dmxdevfilter, *(u16 *)parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_REMOVE_PID:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			ret = -ERESTARTSYS;
			break;
		}
		ret = dvb_dmxdev_remove_pid(dmxdev, dmxdevfilter, *(u16 *)parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

#ifdef CONFIG_DVB_MMAP
	case DMX_REQBUFS:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_vb2_reqbufs(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_QUERYBUF:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_vb2_querybuf(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_EXPBUF:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_vb2_expbuf(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_QBUF:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_vb2_qbuf(&dmxdevfilter->vb2_ctx, parg);
		if (ret == 0 && !dvb_vb2_is_streaming(&dmxdevfilter->vb2_ctx))
			ret = dvb_vb2_stream_on(&dmxdevfilter->vb2_ctx);
		mutex_unlock(&dmxdevfilter->mutex);
		break;

	case DMX_DQBUF:
		if (mutex_lock_interruptible(&dmxdevfilter->mutex)) {
			mutex_unlock(&dmxdev->mutex);
			return -ERESTARTSYS;
		}
		ret = dvb_vb2_dqbuf(&dmxdevfilter->vb2_ctx, parg);
		mutex_unlock(&dmxdevfilter->mutex);
		break;
#endif
	default:
		ret = -ENOTTY;
		break;
	}
	mutex_unlock(&dmxdev->mutex);
	return ret;
}