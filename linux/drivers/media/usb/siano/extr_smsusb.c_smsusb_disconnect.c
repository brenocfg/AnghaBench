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

/* Variables and functions */
 int /*<<< orphan*/  smsusb_term_device (struct usb_interface*) ; 

__attribute__((used)) static void smsusb_disconnect(struct usb_interface *intf)
{
	smsusb_term_device(intf);
}