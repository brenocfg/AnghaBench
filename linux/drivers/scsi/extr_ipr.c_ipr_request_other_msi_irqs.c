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
struct pci_dev {int dummy; } ;
struct ipr_ioa_cfg {int nvectors; int /*<<< orphan*/ * hrrq; TYPE_1__* vectors_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_isr_mhrrq ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipr_request_other_msi_irqs(struct ipr_ioa_cfg *ioa_cfg,
		struct pci_dev *pdev)
{
	int i, rc;

	for (i = 1; i < ioa_cfg->nvectors; i++) {
		rc = request_irq(pci_irq_vector(pdev, i),
			ipr_isr_mhrrq,
			0,
			ioa_cfg->vectors_info[i].desc,
			&ioa_cfg->hrrq[i]);
		if (rc) {
			while (--i >= 0)
				free_irq(pci_irq_vector(pdev, i),
					&ioa_cfg->hrrq[i]);
			return rc;
		}
	}
	return 0;
}