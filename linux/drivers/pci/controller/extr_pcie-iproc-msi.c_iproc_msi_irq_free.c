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
struct iproc_msi {int nr_irqs; TYPE_1__* grps; scalar_t__ nr_cpus; } ;
struct TYPE_2__ {int /*<<< orphan*/  gic_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iproc_msi_irq_free(struct iproc_msi *msi, unsigned int cpu)
{
	int i;

	for (i = cpu; i < msi->nr_irqs; i += msi->nr_cpus) {
		irq_set_chained_handler_and_data(msi->grps[i].gic_irq,
						 NULL, NULL);
	}
}