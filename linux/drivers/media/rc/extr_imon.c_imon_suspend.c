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
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct imon_context {int /*<<< orphan*/  rx_urb_intf1; int /*<<< orphan*/  rx_urb_intf0; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_3__ {int bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 struct imon_context* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imon_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct imon_context *ictx = usb_get_intfdata(intf);
	int ifnum = intf->cur_altsetting->desc.bInterfaceNumber;

	if (ifnum == 0)
		usb_kill_urb(ictx->rx_urb_intf0);
	else
		usb_kill_urb(ictx->rx_urb_intf1);

	return 0;
}