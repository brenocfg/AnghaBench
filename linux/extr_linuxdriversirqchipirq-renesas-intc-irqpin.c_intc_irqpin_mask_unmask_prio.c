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
struct intc_irqpin_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTC_IRQPIN_REG_PRIO ; 
 int /*<<< orphan*/  intc_irqpin_read_modify_write (struct intc_irqpin_priv*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void intc_irqpin_mask_unmask_prio(struct intc_irqpin_priv *p,
					 int irq, int do_mask)
{
	/* The PRIO register is assumed to be 32-bit with fixed 4-bit fields. */
	int bitfield_width = 4;
	int shift = 32 - (irq + 1) * bitfield_width;

	intc_irqpin_read_modify_write(p, INTC_IRQPIN_REG_PRIO,
				      shift, bitfield_width,
				      do_mask ? 0 : (1 << bitfield_width) - 1);
}