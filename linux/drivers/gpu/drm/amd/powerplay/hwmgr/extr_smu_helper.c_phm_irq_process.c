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
typedef  scalar_t__ uint32_t ;
struct amdgpu_iv_entry {scalar_t__ client_id; scalar_t__ src_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_IRQ_CLIENTID_LEGACY ; 
 int /*<<< orphan*/  PCI_BUS_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ SOC15_IH_CLIENTID_ROM_SMUIO ; 
 scalar_t__ SOC15_IH_CLIENTID_THM ; 
 scalar_t__ VISLANDS30_IV_SRCID_CG_TSS_THERMAL_HIGH_TO_LOW ; 
 scalar_t__ VISLANDS30_IV_SRCID_CG_TSS_THERMAL_LOW_TO_HIGH ; 
 scalar_t__ VISLANDS30_IV_SRCID_GPIO_19 ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phm_irq_process(struct amdgpu_device *adev,
			   struct amdgpu_irq_src *source,
			   struct amdgpu_iv_entry *entry)
{
	uint32_t client_id = entry->client_id;
	uint32_t src_id = entry->src_id;

	if (client_id == AMDGPU_IRQ_CLIENTID_LEGACY) {
		if (src_id == VISLANDS30_IV_SRCID_CG_TSS_THERMAL_LOW_TO_HIGH)
			pr_warn("GPU over temperature range detected on PCIe %d:%d.%d!\n",
						PCI_BUS_NUM(adev->pdev->devfn),
						PCI_SLOT(adev->pdev->devfn),
						PCI_FUNC(adev->pdev->devfn));
		else if (src_id == VISLANDS30_IV_SRCID_CG_TSS_THERMAL_HIGH_TO_LOW)
			pr_warn("GPU under temperature range detected on PCIe %d:%d.%d!\n",
					PCI_BUS_NUM(adev->pdev->devfn),
					PCI_SLOT(adev->pdev->devfn),
					PCI_FUNC(adev->pdev->devfn));
		else if (src_id == VISLANDS30_IV_SRCID_GPIO_19)
			pr_warn("GPU Critical Temperature Fault detected on PCIe %d:%d.%d!\n",
					PCI_BUS_NUM(adev->pdev->devfn),
					PCI_SLOT(adev->pdev->devfn),
					PCI_FUNC(adev->pdev->devfn));
	} else if (client_id == SOC15_IH_CLIENTID_THM) {
		if (src_id == 0)
			pr_warn("GPU over temperature range detected on PCIe %d:%d.%d!\n",
						PCI_BUS_NUM(adev->pdev->devfn),
						PCI_SLOT(adev->pdev->devfn),
						PCI_FUNC(adev->pdev->devfn));
		else
			pr_warn("GPU under temperature range detected on PCIe %d:%d.%d!\n",
					PCI_BUS_NUM(adev->pdev->devfn),
					PCI_SLOT(adev->pdev->devfn),
					PCI_FUNC(adev->pdev->devfn));
	} else if (client_id == SOC15_IH_CLIENTID_ROM_SMUIO)
		pr_warn("GPU Critical Temperature Fault detected on PCIe %d:%d.%d!\n",
				PCI_BUS_NUM(adev->pdev->devfn),
				PCI_SLOT(adev->pdev->devfn),
				PCI_FUNC(adev->pdev->devfn));

	return 0;
}