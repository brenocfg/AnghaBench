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
struct imx_keypad {int cols_en_mask; scalar_t__ mmio_base; } ;

/* Variables and functions */
 unsigned short KBD_STAT_KDIE ; 
 unsigned short KBD_STAT_KPKD ; 
 unsigned short KBD_STAT_KPKR ; 
 unsigned short KBD_STAT_KRIE ; 
 scalar_t__ KPCR ; 
 scalar_t__ KPSR ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static void imx_keypad_inhibit(struct imx_keypad *keypad)
{
	unsigned short reg_val;

	/* Inhibit KDI and KRI interrupts. */
	reg_val = readw(keypad->mmio_base + KPSR);
	reg_val &= ~(KBD_STAT_KRIE | KBD_STAT_KDIE);
	reg_val |= KBD_STAT_KPKR | KBD_STAT_KPKD;
	writew(reg_val, keypad->mmio_base + KPSR);

	/* Colums as open drain and disable all rows */
	reg_val = (keypad->cols_en_mask & 0xff) << 8;
	writew(reg_val, keypad->mmio_base + KPCR);
}