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
struct ls_scfg_msir {int index; int gic_irq; int bit_start; int bit_end; int srs; scalar_t__ reg; struct ls_scfg_msi* msi_data; } ;
struct ls_scfg_msi {int /*<<< orphan*/  used; TYPE_1__* cfg; scalar_t__ regs; struct ls_scfg_msir* msir; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int msir_irqs; int ibs_shift; scalar_t__ msir_base; } ;

/* Variables and functions */
 int ENODEV ; 
 int MSI_LS1043V1_1_IRQS_PER_MSIR ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_cpu_mask (int) ; 
 int /*<<< orphan*/  irq_set_affinity (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct ls_scfg_msir*) ; 
 int /*<<< orphan*/  ls_scfg_msi_irq_handler ; 
 scalar_t__ msi_affinity_flag ; 
 int platform_get_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ls_scfg_msi_setup_hwirq(struct ls_scfg_msi *msi_data, int index)
{
	struct ls_scfg_msir *msir;
	int virq, i, hwirq;

	virq = platform_get_irq(msi_data->pdev, index);
	if (virq <= 0)
		return -ENODEV;

	msir = &msi_data->msir[index];
	msir->index = index;
	msir->msi_data = msi_data;
	msir->gic_irq = virq;
	msir->reg = msi_data->regs + msi_data->cfg->msir_base + 4 * index;

	if (msi_data->cfg->msir_irqs == MSI_LS1043V1_1_IRQS_PER_MSIR) {
		msir->bit_start = 32 - ((msir->index + 1) *
				  MSI_LS1043V1_1_IRQS_PER_MSIR);
		msir->bit_end = msir->bit_start +
				MSI_LS1043V1_1_IRQS_PER_MSIR - 1;
	} else {
		msir->bit_start = 0;
		msir->bit_end = msi_data->cfg->msir_irqs - 1;
	}

	irq_set_chained_handler_and_data(msir->gic_irq,
					 ls_scfg_msi_irq_handler,
					 msir);

	if (msi_affinity_flag) {
		/* Associate MSIR interrupt to the cpu */
		irq_set_affinity(msir->gic_irq, get_cpu_mask(index));
		msir->srs = 0; /* This value is determined by the CPU */
	} else
		msir->srs = index;

	/* Release the hwirqs corresponding to this MSIR */
	if (!msi_affinity_flag || msir->index == 0) {
		for (i = 0; i < msi_data->cfg->msir_irqs; i++) {
			hwirq = i << msi_data->cfg->ibs_shift | msir->index;
			bitmap_clear(msi_data->used, hwirq, 1);
		}
	}

	return 0;
}