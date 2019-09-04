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
struct intc_irqpin_iomem {int /*<<< orphan*/  iomem; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void intc_irqpin_write(struct intc_irqpin_priv *p,
				     int reg, unsigned long data)
{
	struct intc_irqpin_iomem *i = &p->iomem[reg];

	i->write(i->iomem, data);
}