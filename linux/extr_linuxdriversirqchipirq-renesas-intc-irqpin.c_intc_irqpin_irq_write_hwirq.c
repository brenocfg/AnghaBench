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
 int /*<<< orphan*/  intc_irqpin_hwirq_mask (struct intc_irqpin_priv*,int,int) ; 
 int /*<<< orphan*/  intc_irqpin_write (struct intc_irqpin_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void intc_irqpin_irq_write_hwirq(struct intc_irqpin_priv *p,
					       int reg, int hw_irq)
{
	intc_irqpin_write(p, reg, intc_irqpin_hwirq_mask(p, reg, hw_irq));
}