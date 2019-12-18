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
struct intel_th_driver {int /*<<< orphan*/  (* irq ) (TYPE_2__*) ;} ;
struct intel_th {int num_thdevs; TYPE_2__** thdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ INTEL_TH_OUTPUT ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 struct intel_th_driver* to_intel_th_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t intel_th_irq(int irq, void *data)
{
	struct intel_th *th = data;
	irqreturn_t ret = IRQ_NONE;
	struct intel_th_driver *d;
	int i;

	for (i = 0; i < th->num_thdevs; i++) {
		if (th->thdev[i]->type != INTEL_TH_OUTPUT)
			continue;

		d = to_intel_th_driver(th->thdev[i]->dev.driver);
		if (d && d->irq)
			ret |= d->irq(th->thdev[i]);
	}

	if (ret == IRQ_NONE)
		pr_warn_ratelimited("nobody cared for irq\n");

	return ret;
}