#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intc_irqpin_irq {int /*<<< orphan*/  domain_irq; int /*<<< orphan*/  hw_irq; int /*<<< orphan*/  requested_irq; TYPE_2__* p; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intc_irqpin_dbg(struct intc_irqpin_irq *i, char *str)
{
	dev_dbg(&i->p->pdev->dev, "%s (%d:%d:%d)\n",
		str, i->requested_irq, i->hw_irq, i->domain_irq);
}