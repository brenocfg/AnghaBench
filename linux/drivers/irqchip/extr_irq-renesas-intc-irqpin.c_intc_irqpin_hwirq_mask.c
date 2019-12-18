#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intc_irqpin_priv {TYPE_1__* iomem; } ;
struct TYPE_2__ {int width; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 

__attribute__((used)) static inline unsigned long intc_irqpin_hwirq_mask(struct intc_irqpin_priv *p,
						   int reg, int hw_irq)
{
	return BIT((p->iomem[reg].width - 1) - hw_irq);
}