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
struct usb_lcd {int disconnected; int /*<<< orphan*/  kref; int /*<<< orphan*/  submitted; int /*<<< orphan*/  io_rwsem; } ;
struct usb_interface {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_class ; 
 int /*<<< orphan*/  lcd_delete ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usb_lcd* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lcd_disconnect(struct usb_interface *interface)
{
	struct usb_lcd *dev = usb_get_intfdata(interface);
	int minor = interface->minor;

	/* give back our minor */
	usb_deregister_dev(interface, &lcd_class);

	down_write(&dev->io_rwsem);
	dev->disconnected = 1;
	up_write(&dev->io_rwsem);

	usb_kill_anchored_urbs(&dev->submitted);

	/* decrement our usage count */
	kref_put(&dev->kref, lcd_delete);

	dev_info(&interface->dev, "USB LCD #%d now disconnected\n", minor);
}