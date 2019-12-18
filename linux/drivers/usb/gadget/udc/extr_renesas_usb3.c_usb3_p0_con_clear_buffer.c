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
 int /*<<< orphan*/  P0_CON_BCLR ; 
 int /*<<< orphan*/  USB3_P0_CON ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb3_wait (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3_p0_con_clear_buffer(struct renesas_usb3 *usb3)
{
	usb3_set_bit(usb3, P0_CON_BCLR, USB3_P0_CON);

	return usb3_wait(usb3, USB3_P0_CON, P0_CON_BCLR, 0);
}