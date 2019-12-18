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
 int /*<<< orphan*/  DRD_CON_PERI_CON ; 
 int /*<<< orphan*/  USB3_DRD_CON ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_set_mode(struct renesas_usb3 *usb3, bool host)
{
	if (host)
		usb3_clear_bit(usb3, DRD_CON_PERI_CON, USB3_DRD_CON);
	else
		usb3_set_bit(usb3, DRD_CON_PERI_CON, USB3_DRD_CON);
}