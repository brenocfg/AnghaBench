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
struct ls_scfg_msir {scalar_t__ gic_irq; int index; struct ls_scfg_msi* msi_data; } ;
struct ls_scfg_msi {int /*<<< orphan*/  used; TYPE_1__* cfg; } ;
struct TYPE_2__ {int msir_irqs; int ibs_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ls_scfg_msi_teardown_hwirq(struct ls_scfg_msir *msir)
{
	struct ls_scfg_msi *msi_data = msir->msi_data;
	int i, hwirq;

	if (msir->gic_irq > 0)
		irq_set_chained_handler_and_data(msir->gic_irq, NULL, NULL);

	for (i = 0; i < msi_data->cfg->msir_irqs; i++) {
		hwirq = i << msi_data->cfg->ibs_shift | msir->index;
		bitmap_set(msi_data->used, hwirq, 1);
	}

	return 0;
}