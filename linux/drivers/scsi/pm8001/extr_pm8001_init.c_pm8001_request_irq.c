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
typedef  int u32 ;
struct pm8001_hba_info {int /*<<< orphan*/  shost; TYPE_1__* irq_vector; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; scalar_t__ msix_cap; } ;
struct TYPE_2__ {struct pm8001_hba_info* drv_inst; scalar_t__ irq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHOST_TO_SAS_HA (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_msi_enabled () ; 
 int /*<<< orphan*/  pm8001_interrupt_handler_intx ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 
 int pm8001_setup_msix (struct pm8001_hba_info*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pm8001_request_irq(struct pm8001_hba_info *pm8001_ha)
{
	struct pci_dev *pdev;
	int rc;

	pdev = pm8001_ha->pdev;

#ifdef PM8001_USE_MSIX
	if (pdev->msix_cap && pci_msi_enabled())
		return pm8001_setup_msix(pm8001_ha);
	else {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("MSIX not supported!!!\n"));
		goto intx;
	}
#endif

intx:
	/* initialize the INT-X interrupt */
	pm8001_ha->irq_vector[0].irq_id = 0;
	pm8001_ha->irq_vector[0].drv_inst = pm8001_ha;
	rc = request_irq(pdev->irq, pm8001_interrupt_handler_intx, IRQF_SHARED,
		DRV_NAME, SHOST_TO_SAS_HA(pm8001_ha->shost));
	return rc;
}