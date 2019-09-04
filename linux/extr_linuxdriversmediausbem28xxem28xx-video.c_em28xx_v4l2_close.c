#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct file {int dummy; } ;
struct em28xx_v4l2 {int users; int /*<<< orphan*/  ref; int /*<<< orphan*/  v4l2_dev; } ;
struct em28xx {int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; TYPE_1__* intf; scalar_t__ alt; scalar_t__ disconnected; struct em28xx_v4l2* v4l2; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_SUSPEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  em28xx_free_device ; 
 int /*<<< orphan*/  em28xx_free_v4l2 ; 
 int /*<<< orphan*/  em28xx_set_mode (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,...) ; 
 struct usb_device* interface_to_usbdev (TYPE_1__*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  standby ; 
 int /*<<< orphan*/  tuner ; 
 int usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_fop_release (struct file*) ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int em28xx_v4l2_close(struct file *filp)
{
	struct em28xx         *dev  = video_drvdata(filp);
	struct em28xx_v4l2    *v4l2 = dev->v4l2;
	struct usb_device *udev = interface_to_usbdev(dev->intf);
	int              err;

	em28xx_videodbg("users=%d\n", v4l2->users);

	vb2_fop_release(filp);
	mutex_lock(&dev->lock);

	if (v4l2->users == 1) {
		/* No sense to try to write to the device */
		if (dev->disconnected)
			goto exit;

		/* Save some power by putting tuner to sleep */
		v4l2_device_call_all(&v4l2->v4l2_dev, 0, tuner, standby);

		/* do this before setting alternate! */
		em28xx_set_mode(dev, EM28XX_SUSPEND);

		/* set alternate 0 */
		dev->alt = 0;
		em28xx_videodbg("setting alternate 0\n");
		err = usb_set_interface(udev, 0, 0);
		if (err < 0) {
			dev_err(&dev->intf->dev,
				"cannot change alternate number to 0 (error=%i)\n",
				err);
		}
	}

exit:
	v4l2->users--;
	kref_put(&v4l2->ref, em28xx_free_v4l2);
	mutex_unlock(&dev->lock);
	kref_put(&dev->ref, em28xx_free_device);

	return 0;
}