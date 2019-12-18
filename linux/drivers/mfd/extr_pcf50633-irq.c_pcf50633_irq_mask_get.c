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
typedef  size_t u8 ;
struct pcf50633 {size_t* mask_regs; } ;

/* Variables and functions */

int pcf50633_irq_mask_get(struct pcf50633 *pcf, int irq)
{
	u8 reg, bits;

	reg =  irq >> 3;
	bits = 1 << (irq & 0x07);

	return pcf->mask_regs[reg] & bits;
}