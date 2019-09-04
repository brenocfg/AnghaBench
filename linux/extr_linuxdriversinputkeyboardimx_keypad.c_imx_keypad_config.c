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
struct imx_keypad {int rows_en_mask; int cols_en_mask; scalar_t__ mmio_base; } ;

/* Variables and functions */
 unsigned short KBD_STAT_KDIE ; 
 unsigned short KBD_STAT_KDSC ; 
 unsigned short KBD_STAT_KPKD ; 
 unsigned short KBD_STAT_KPKR ; 
 unsigned short KBD_STAT_KRIE ; 
 unsigned short KBD_STAT_KRSS ; 
 scalar_t__ KDDR ; 
 scalar_t__ KPCR ; 
 scalar_t__ KPDR ; 
 scalar_t__ KPSR ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static void imx_keypad_config(struct imx_keypad *keypad)
{
	unsigned short reg_val;

	/*
	 * Include enabled rows in interrupt generation (KPCR[7:0])
	 * Configure keypad columns as open-drain (KPCR[15:8])
	 */
	reg_val = readw(keypad->mmio_base + KPCR);
	reg_val |= keypad->rows_en_mask & 0xff;		/* rows */
	reg_val |= (keypad->cols_en_mask & 0xff) << 8;	/* cols */
	writew(reg_val, keypad->mmio_base + KPCR);

	/* Write 0's to KPDR[15:8] (Colums) */
	reg_val = readw(keypad->mmio_base + KPDR);
	reg_val &= 0x00ff;
	writew(reg_val, keypad->mmio_base + KPDR);

	/* Configure columns as output, rows as input (KDDR[15:0]) */
	writew(0xff00, keypad->mmio_base + KDDR);

	/*
	 * Clear Key Depress and Key Release status bit.
	 * Clear both synchronizer chain.
	 */
	reg_val = readw(keypad->mmio_base + KPSR);
	reg_val |= KBD_STAT_KPKR | KBD_STAT_KPKD |
		   KBD_STAT_KDSC | KBD_STAT_KRSS;
	writew(reg_val, keypad->mmio_base + KPSR);

	/* Enable KDI and disable KRI (avoid false release events). */
	reg_val |= KBD_STAT_KDIE;
	reg_val &= ~KBD_STAT_KRIE;
	writew(reg_val, keypad->mmio_base + KPSR);
}