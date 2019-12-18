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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct fb_info {int /*<<< orphan*/  dev; } ;
struct dlfb_data {int virtualized; int /*<<< orphan*/  usb_active; struct fb_info* info; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlfb_free_urb_list (struct dlfb_data*) ; 
 int /*<<< orphan*/  edid_attr ; 
 int /*<<< orphan*/ * fb_device_attrs ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 
 struct dlfb_data* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void dlfb_usb_disconnect(struct usb_interface *intf)
{
	struct dlfb_data *dlfb;
	struct fb_info *info;
	int i;

	dlfb = usb_get_intfdata(intf);
	info = dlfb->info;

	dev_dbg(&intf->dev, "USB disconnect starting\n");

	/* we virtualize until all fb clients release. Then we free */
	dlfb->virtualized = true;

	/* When non-active we'll update virtual framebuffer, but no new urbs */
	atomic_set(&dlfb->usb_active, 0);

	/* this function will wait for all in-flight urbs to complete */
	dlfb_free_urb_list(dlfb);

	/* remove udlfb's sysfs interfaces */
	for (i = 0; i < ARRAY_SIZE(fb_device_attrs); i++)
		device_remove_file(info->dev, &fb_device_attrs[i]);
	device_remove_bin_file(info->dev, &edid_attr);

	unregister_framebuffer(info);
}