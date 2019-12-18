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
struct renesas_usb3 {int disabled_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb3_reset_epc (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_start_usb2_connection (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_start_usb3_connection (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_epc_int_1_bus_reset(struct renesas_usb3 *usb3)
{
	usb3_reset_epc(usb3);
	if (usb3->disabled_count < 3)
		usb3_start_usb3_connection(usb3);
	else
		usb3_start_usb2_connection(usb3);
}