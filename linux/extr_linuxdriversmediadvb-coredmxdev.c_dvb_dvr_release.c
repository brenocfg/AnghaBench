#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {int users; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  readers; struct dmxdev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct dmxdev {int exit; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; TYPE_1__ dvr_buffer; int /*<<< orphan*/  dvr_vb2_ctx; scalar_t__ may_do_mmap; int /*<<< orphan*/  dvr_orig_fe; TYPE_2__* demux; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* connect_frontend ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disconnect_frontend ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 scalar_t__ dvb_vb2_is_streaming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_vb2_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_vb2_stream_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_dvr_release(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct dmxdev *dmxdev = dvbdev->priv;

	mutex_lock(&dmxdev->mutex);

	if ((file->f_flags & O_ACCMODE) == O_WRONLY) {
		dmxdev->demux->disconnect_frontend(dmxdev->demux);
		dmxdev->demux->connect_frontend(dmxdev->demux,
						dmxdev->dvr_orig_fe);
	}

	if (((file->f_flags & O_ACCMODE) == O_RDONLY) ||
	    dmxdev->may_do_mmap) {
		if (dmxdev->may_do_mmap) {
			if (dvb_vb2_is_streaming(&dmxdev->dvr_vb2_ctx))
				dvb_vb2_stream_off(&dmxdev->dvr_vb2_ctx);
			dvb_vb2_release(&dmxdev->dvr_vb2_ctx);
		}
		dvbdev->readers++;
		if (dmxdev->dvr_buffer.data) {
			void *mem = dmxdev->dvr_buffer.data;
			/*memory barrier*/
			mb();
			spin_lock_irq(&dmxdev->lock);
			dmxdev->dvr_buffer.data = NULL;
			spin_unlock_irq(&dmxdev->lock);
			vfree(mem);
		}
	}
	/* TODO */
	dvbdev->users--;
	if (dvbdev->users == 1 && dmxdev->exit == 1) {
		mutex_unlock(&dmxdev->mutex);
		wake_up(&dvbdev->wait_queue);
	} else
		mutex_unlock(&dmxdev->mutex);

	return 0;
}