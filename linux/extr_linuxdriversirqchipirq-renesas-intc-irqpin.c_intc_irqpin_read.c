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
struct intc_irqpin_priv {struct intc_irqpin_iomem* iomem; } ;
struct intc_irqpin_iomem {unsigned long (* read ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 unsigned long stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long intc_irqpin_read(struct intc_irqpin_priv *p,
					     int reg)
{
	struct intc_irqpin_iomem *i = &p->iomem[reg];

	return i->read(i->iomem);
}