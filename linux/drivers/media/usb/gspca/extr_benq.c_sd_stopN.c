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
struct usb_interface {scalar_t__ num_altsetting; } ;
struct gspca_dev {int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct usb_interface *intf;

	reg_w(gspca_dev, 0x003c, 0x0003);
	reg_w(gspca_dev, 0x003c, 0x0004);
	reg_w(gspca_dev, 0x003c, 0x0005);
	reg_w(gspca_dev, 0x003c, 0x0006);
	reg_w(gspca_dev, 0x003c, 0x0007);

	intf = usb_ifnum_to_if(gspca_dev->dev, gspca_dev->iface);
	usb_set_interface(gspca_dev->dev, gspca_dev->iface,
					intf->num_altsetting - 1);
}