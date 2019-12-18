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
struct usb_interface {int dummy; } ;
struct atp {int /*<<< orphan*/  urb; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct atp* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atp_suspend(struct usb_interface *iface, pm_message_t message)
{
	struct atp *dev = usb_get_intfdata(iface);

	usb_kill_urb(dev->urb);
	return 0;
}