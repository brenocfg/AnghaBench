#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * funcs; void* max_height; void* min_height; void* max_width; void* min_width; } ;
struct drm_device {TYPE_4__ mode_config; struct gm12u320_device* dev_private; } ;
struct TYPE_7__ {int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;
struct gm12u320_device {int /*<<< orphan*/  conn; int /*<<< orphan*/  pipe; struct drm_device dev; TYPE_3__ fb_update; int /*<<< orphan*/  udev; } ;
struct TYPE_5__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* GM12U320_HEIGHT ; 
 void* GM12U320_USER_WIDTH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_dev_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gm12u320_conn_init (struct gm12u320_device*) ; 
 int /*<<< orphan*/  gm12u320_drm_driver ; 
 int /*<<< orphan*/  gm12u320_fb_update_work ; 
 int /*<<< orphan*/  gm12u320_mode_config_funcs ; 
 int /*<<< orphan*/  gm12u320_pipe_formats ; 
 int /*<<< orphan*/  gm12u320_pipe_funcs ; 
 int /*<<< orphan*/  gm12u320_pipe_modifiers ; 
 int gm12u320_set_ecomode (struct gm12u320_device*) ; 
 int gm12u320_usb_alloc (struct gm12u320_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct gm12u320_device*) ; 
 struct gm12u320_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct drm_device*) ; 

__attribute__((used)) static int gm12u320_usb_probe(struct usb_interface *interface,
			      const struct usb_device_id *id)
{
	struct gm12u320_device *gm12u320;
	struct drm_device *dev;
	int ret;

	/*
	 * The gm12u320 presents itself to the system as 2 usb mass-storage
	 * interfaces, we only care about / need the first one.
	 */
	if (interface->cur_altsetting->desc.bInterfaceNumber != 0)
		return -ENODEV;

	gm12u320 = kzalloc(sizeof(*gm12u320), GFP_KERNEL);
	if (gm12u320 == NULL)
		return -ENOMEM;

	gm12u320->udev = interface_to_usbdev(interface);
	INIT_WORK(&gm12u320->fb_update.work, gm12u320_fb_update_work);
	mutex_init(&gm12u320->fb_update.lock);
	init_waitqueue_head(&gm12u320->fb_update.waitq);

	dev = &gm12u320->dev;
	ret = drm_dev_init(dev, &gm12u320_drm_driver, &interface->dev);
	if (ret) {
		kfree(gm12u320);
		return ret;
	}
	dev->dev_private = gm12u320;

	drm_mode_config_init(dev);
	dev->mode_config.min_width = GM12U320_USER_WIDTH;
	dev->mode_config.max_width = GM12U320_USER_WIDTH;
	dev->mode_config.min_height = GM12U320_HEIGHT;
	dev->mode_config.max_height = GM12U320_HEIGHT;
	dev->mode_config.funcs = &gm12u320_mode_config_funcs;

	ret = gm12u320_usb_alloc(gm12u320);
	if (ret)
		goto err_put;

	ret = gm12u320_set_ecomode(gm12u320);
	if (ret)
		goto err_put;

	ret = gm12u320_conn_init(gm12u320);
	if (ret)
		goto err_put;

	ret = drm_simple_display_pipe_init(&gm12u320->dev,
					   &gm12u320->pipe,
					   &gm12u320_pipe_funcs,
					   gm12u320_pipe_formats,
					   ARRAY_SIZE(gm12u320_pipe_formats),
					   gm12u320_pipe_modifiers,
					   &gm12u320->conn);
	if (ret)
		goto err_put;

	drm_mode_config_reset(dev);

	usb_set_intfdata(interface, dev);
	ret = drm_dev_register(dev, 0);
	if (ret)
		goto err_put;

	drm_fbdev_generic_setup(dev, 0);

	return 0;

err_put:
	drm_dev_put(dev);
	return ret;
}