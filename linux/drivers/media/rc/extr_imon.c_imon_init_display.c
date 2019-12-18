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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_1__ dev; } ;
struct imon_context {scalar_t__ display_type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IMON_DISPLAY_TYPE_LCD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  imon_display_attr_group ; 
 int /*<<< orphan*/  imon_lcd_class ; 
 int /*<<< orphan*/  imon_vfd_class ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imon_init_display(struct imon_context *ictx,
			      struct usb_interface *intf)
{
	int ret;

	dev_dbg(ictx->dev, "Registering iMON display with sysfs\n");

	/* set up sysfs entry for built-in clock */
	ret = sysfs_create_group(&intf->dev.kobj, &imon_display_attr_group);
	if (ret)
		dev_err(ictx->dev, "Could not create display sysfs entries(%d)",
			ret);

	if (ictx->display_type == IMON_DISPLAY_TYPE_LCD)
		ret = usb_register_dev(intf, &imon_lcd_class);
	else
		ret = usb_register_dev(intf, &imon_vfd_class);
	if (ret)
		/* Not a fatal error, so ignore */
		dev_info(ictx->dev, "could not get a minor number for display\n");

}