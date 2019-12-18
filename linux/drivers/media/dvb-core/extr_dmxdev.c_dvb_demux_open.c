#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {scalar_t__ state; int /*<<< orphan*/  users; int /*<<< orphan*/  timer; int /*<<< orphan*/  type; int /*<<< orphan*/  vb2_ctx; int /*<<< orphan*/  buffer; int /*<<< orphan*/  mutex; struct dmxdev* priv; } ;
struct dmxdev_filter {scalar_t__ state; int /*<<< orphan*/  users; int /*<<< orphan*/  timer; int /*<<< orphan*/  type; int /*<<< orphan*/  vb2_ctx; int /*<<< orphan*/  buffer; int /*<<< orphan*/  mutex; struct dmxdev* priv; } ;
struct dmxdev {int filternum; int may_do_mmap; int /*<<< orphan*/  mutex; struct dvb_device* filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMXDEV_STATE_ALLOCATED ; 
 scalar_t__ DMXDEV_STATE_FREE ; 
 int /*<<< orphan*/  DMXDEV_TYPE_NONE ; 
 int EINVAL ; 
 int EMFILE ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_state_set (struct dvb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_timeout ; 
 int /*<<< orphan*/  dvb_ringbuffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dvb_vb2_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_demux_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct dmxdev *dmxdev = dvbdev->priv;
	int i;
	struct dmxdev_filter *dmxdevfilter;

	if (!dmxdev->filter)
		return -EINVAL;

	if (mutex_lock_interruptible(&dmxdev->mutex))
		return -ERESTARTSYS;

	for (i = 0; i < dmxdev->filternum; i++)
		if (dmxdev->filter[i].state == DMXDEV_STATE_FREE)
			break;

	if (i == dmxdev->filternum) {
		mutex_unlock(&dmxdev->mutex);
		return -EMFILE;
	}

	dmxdevfilter = &dmxdev->filter[i];
	mutex_init(&dmxdevfilter->mutex);
	file->private_data = dmxdevfilter;

#ifdef CONFIG_DVB_MMAP
	dmxdev->may_do_mmap = 1;
#else
	dmxdev->may_do_mmap = 0;
#endif

	dvb_ringbuffer_init(&dmxdevfilter->buffer, NULL, 8192);
	dvb_vb2_init(&dmxdevfilter->vb2_ctx, "demux_filter",
		     file->f_flags & O_NONBLOCK);
	dmxdevfilter->type = DMXDEV_TYPE_NONE;
	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_ALLOCATED);
	timer_setup(&dmxdevfilter->timer, dvb_dmxdev_filter_timeout, 0);

	dvbdev->users++;

	mutex_unlock(&dmxdev->mutex);
	return 0;
}