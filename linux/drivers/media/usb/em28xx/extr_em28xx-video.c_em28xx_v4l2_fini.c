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
struct em28xx_v4l2 {int /*<<< orphan*/  ref; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  vdev; int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  radio_dev; } ;
struct em28xx {int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; TYPE_1__* intf; int /*<<< orphan*/  has_video; scalar_t__ is_audio_only; struct em28xx_v4l2* v4l2; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_ANALOG_MODE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  em28xx_free_device ; 
 int /*<<< orphan*/  em28xx_free_v4l2 ; 
 int /*<<< orphan*/  em28xx_uninit_usb_xfer (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_v4l2_media_release (struct em28xx*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_v4l2_fini(struct em28xx *dev)
{
	struct em28xx_v4l2 *v4l2 = dev->v4l2;

	if (dev->is_audio_only) {
		/* Shouldn't initialize IR for this interface */
		return 0;
	}

	if (!dev->has_video) {
		/* This device does not support the v4l2 extension */
		return 0;
	}

	if (!v4l2)
		return 0;

	dev_info(&dev->intf->dev, "Closing video extension\n");

	mutex_lock(&dev->lock);

	v4l2_device_disconnect(&v4l2->v4l2_dev);

	em28xx_uninit_usb_xfer(dev, EM28XX_ANALOG_MODE);

	em28xx_v4l2_media_release(dev);

	if (video_is_registered(&v4l2->radio_dev)) {
		dev_info(&dev->intf->dev, "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->radio_dev));
		video_unregister_device(&v4l2->radio_dev);
	}
	if (video_is_registered(&v4l2->vbi_dev)) {
		dev_info(&dev->intf->dev, "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->vbi_dev));
		video_unregister_device(&v4l2->vbi_dev);
	}
	if (video_is_registered(&v4l2->vdev)) {
		dev_info(&dev->intf->dev, "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->vdev));
		video_unregister_device(&v4l2->vdev);
	}

	v4l2_ctrl_handler_free(&v4l2->ctrl_handler);
	v4l2_device_unregister(&v4l2->v4l2_dev);

	kref_put(&v4l2->ref, em28xx_free_v4l2);

	mutex_unlock(&dev->lock);

	kref_put(&dev->ref, em28xx_free_device);

	return 0;
}