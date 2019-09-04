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
struct TYPE_4__ {int /*<<< orphan*/  dma_get_required_mask; int /*<<< orphan*/  dma_set_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev_setup; int /*<<< orphan*/  dma_bus_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  dma_get_required_mask_pSeriesLP ; 
 int /*<<< orphan*/  dma_iommu_ops ; 
 int /*<<< orphan*/  dma_set_mask_pSeriesLP ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_mem_nb ; 
 int /*<<< orphan*/  iommu_reconfig_nb ; 
 scalar_t__ of_chosen ; 
 scalar_t__ of_get_property (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_reconfig_notifier_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dma_bus_setup_pSeries ; 
 int /*<<< orphan*/  pci_dma_bus_setup_pSeriesLP ; 
 int /*<<< orphan*/  pci_dma_dev_setup_pSeries ; 
 int /*<<< orphan*/  pci_dma_dev_setup_pSeriesLP ; 
 TYPE_2__ ppc_md ; 
 TYPE_1__ pseries_pci_controller_ops ; 
 int /*<<< orphan*/  register_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pci_dma_ops (int /*<<< orphan*/ *) ; 

void iommu_init_early_pSeries(void)
{
	if (of_chosen && of_get_property(of_chosen, "linux,iommu-off", NULL))
		return;

	if (firmware_has_feature(FW_FEATURE_LPAR)) {
		pseries_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pSeriesLP;
		pseries_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pSeriesLP;
		ppc_md.dma_set_mask = dma_set_mask_pSeriesLP;
		ppc_md.dma_get_required_mask = dma_get_required_mask_pSeriesLP;
	} else {
		pseries_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pSeries;
		pseries_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pSeries;
	}


	of_reconfig_notifier_register(&iommu_reconfig_nb);
	register_memory_notifier(&iommu_mem_nb);

	set_pci_dma_ops(&dma_iommu_ops);
}