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
 int /*<<< orphan*/  USB30_CON_B3_PLLWAKE ; 
 int /*<<< orphan*/  USB3_USB30_CON ; 
 int /*<<< orphan*/  USB_INT_1_B3_PLLWKUP ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_disable_irq_1 (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_start_usb3_connection (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_epc_int_1_pll_wakeup(struct renesas_usb3 *usb3)
{
	usb3_disable_irq_1(usb3, USB_INT_1_B3_PLLWKUP);
	usb3_clear_bit(usb3, USB30_CON_B3_PLLWAKE, USB3_USB30_CON);
	usb3_start_usb3_connection(usb3);
}