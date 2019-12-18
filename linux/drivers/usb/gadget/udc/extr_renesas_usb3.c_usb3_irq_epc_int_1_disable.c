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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb3_irq_epc_int_1_resume (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_stop_usb3_connection (struct renesas_usb3*) ; 
 scalar_t__ usb3_wakeup_usb2_phy (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_epc_int_1_disable(struct renesas_usb3 *usb3)
{
	usb3_stop_usb3_connection(usb3);
	if (usb3_wakeup_usb2_phy(usb3))
		usb3_irq_epc_int_1_resume(usb3);
}