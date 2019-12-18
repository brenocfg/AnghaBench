#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct tm6000_fh {int /*<<< orphan*/  fh; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  radio; struct tm6000_core* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_3__ {scalar_t__ endp; } ;
struct tm6000_core {int /*<<< orphan*/  lock; TYPE_2__ isoc_in; int /*<<< orphan*/  udev; TYPE_1__ int_in; int /*<<< orphan*/  users; } ;
struct file {struct tm6000_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_DEBUG_OPEN ; 
 int /*<<< orphan*/  dprintk (struct tm6000_core*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tm6000_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_free (struct tm6000_core*,struct tm6000_fh*) ; 
 int /*<<< orphan*/  tm6000_ir_int_start (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_ir_int_stop (struct tm6000_core*) ; 
 int /*<<< orphan*/  tm6000_uninit_isoc (struct tm6000_core*) ; 
 int /*<<< orphan*/  usb_reset_configuration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tm6000_release(struct file *file)
{
	struct tm6000_fh         *fh = file->private_data;
	struct tm6000_core      *dev = fh->dev;
	struct video_device    *vdev = video_devdata(file);

	dprintk(dev, V4L2_DEBUG_OPEN, "tm6000: close called (dev=%s, users=%d)\n",
		video_device_node_name(vdev), dev->users);

	mutex_lock(&dev->lock);
	dev->users--;

	res_free(dev, fh);

	if (!dev->users) {
		tm6000_uninit_isoc(dev);

		/* Stop interrupt USB pipe */
		tm6000_ir_int_stop(dev);

		usb_reset_configuration(dev->udev);

		if (dev->int_in.endp)
			usb_set_interface(dev->udev,
					dev->isoc_in.bInterfaceNumber, 2);
		else
			usb_set_interface(dev->udev,
					dev->isoc_in.bInterfaceNumber, 0);

		/* Start interrupt USB pipe */
		tm6000_ir_int_start(dev);

		if (!fh->radio)
			videobuf_mmap_free(&fh->vb_vidq);
	}
	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);
	kfree(fh);
	mutex_unlock(&dev->lock);

	return 0;
}