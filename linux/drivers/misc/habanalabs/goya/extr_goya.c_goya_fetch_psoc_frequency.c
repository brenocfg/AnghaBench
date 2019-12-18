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
struct asic_fixed_properties {void* psoc_pci_pll_div_factor; void* psoc_pci_pll_od; void* psoc_pci_pll_nf; void* psoc_pci_pll_nr; } ;
struct hl_device {struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_DIV_FACTOR_1 ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_NF ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_NR ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_OD ; 

__attribute__((used)) static void goya_fetch_psoc_frequency(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;

	prop->psoc_pci_pll_nr = RREG32(mmPSOC_PCI_PLL_NR);
	prop->psoc_pci_pll_nf = RREG32(mmPSOC_PCI_PLL_NF);
	prop->psoc_pci_pll_od = RREG32(mmPSOC_PCI_PLL_OD);
	prop->psoc_pci_pll_div_factor = RREG32(mmPSOC_PCI_PLL_DIV_FACTOR_1);
}