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
 int /*<<< orphan*/  USB_INT_1_B2_RSUM ; 
 int /*<<< orphan*/  usb3_disable_irq_1 (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_start_usb2_connection (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_transition_to_default_state (struct renesas_usb3*,int) ; 

__attribute__((used)) static void usb3_irq_epc_int_1_resume(struct renesas_usb3 *usb3)
{
	usb3_disable_irq_1(usb3, USB_INT_1_B2_RSUM);
	usb3_start_usb2_connection(usb3);
	usb3_transition_to_default_state(usb3, false);
}