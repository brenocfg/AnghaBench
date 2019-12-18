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
struct usb_gadget {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 TYPE_1__ dbgp ; 
 int /*<<< orphan*/  dbgp_disable_ep () ; 
 int /*<<< orphan*/  gserial_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dbgp_disconnect(struct usb_gadget *gadget)
{
#ifdef CONFIG_USB_G_DBGP_PRINTK
	dbgp_disable_ep();
#else
	gserial_disconnect(dbgp.serial);
#endif
}