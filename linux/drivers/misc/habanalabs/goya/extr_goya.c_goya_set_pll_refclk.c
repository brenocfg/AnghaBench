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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCPU_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmCPU_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmCPU_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmCPU_PLL_DIV_SEL_3 ; 
 int /*<<< orphan*/  mmIC_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmIC_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmIC_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmIC_PLL_DIV_SEL_3 ; 
 int /*<<< orphan*/  mmMC_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmMC_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmMC_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmMC_PLL_DIV_SEL_3 ; 
 int /*<<< orphan*/  mmPSOC_EMMC_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmPSOC_EMMC_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmPSOC_EMMC_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmPSOC_EMMC_PLL_DIV_SEL_3 ; 
 int /*<<< orphan*/  mmPSOC_MME_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmPSOC_MME_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmPSOC_MME_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmPSOC_MME_PLL_DIV_SEL_3 ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmPSOC_PCI_PLL_DIV_SEL_3 ; 
 int /*<<< orphan*/  mmTPC_PLL_DIV_SEL_0 ; 
 int /*<<< orphan*/  mmTPC_PLL_DIV_SEL_1 ; 
 int /*<<< orphan*/  mmTPC_PLL_DIV_SEL_2 ; 
 int /*<<< orphan*/  mmTPC_PLL_DIV_SEL_3 ; 

__attribute__((used)) static void goya_set_pll_refclk(struct hl_device *hdev)
{
	WREG32(mmCPU_PLL_DIV_SEL_0, 0x0);
	WREG32(mmCPU_PLL_DIV_SEL_1, 0x0);
	WREG32(mmCPU_PLL_DIV_SEL_2, 0x0);
	WREG32(mmCPU_PLL_DIV_SEL_3, 0x0);

	WREG32(mmIC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmIC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmIC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmIC_PLL_DIV_SEL_3, 0x0);

	WREG32(mmMC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmMC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmMC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmMC_PLL_DIV_SEL_3, 0x0);

	WREG32(mmPSOC_MME_PLL_DIV_SEL_0, 0x0);
	WREG32(mmPSOC_MME_PLL_DIV_SEL_1, 0x0);
	WREG32(mmPSOC_MME_PLL_DIV_SEL_2, 0x0);
	WREG32(mmPSOC_MME_PLL_DIV_SEL_3, 0x0);

	WREG32(mmPSOC_PCI_PLL_DIV_SEL_0, 0x0);
	WREG32(mmPSOC_PCI_PLL_DIV_SEL_1, 0x0);
	WREG32(mmPSOC_PCI_PLL_DIV_SEL_2, 0x0);
	WREG32(mmPSOC_PCI_PLL_DIV_SEL_3, 0x0);

	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmPSOC_EMMC_PLL_DIV_SEL_3, 0x0);

	WREG32(mmTPC_PLL_DIV_SEL_0, 0x0);
	WREG32(mmTPC_PLL_DIV_SEL_1, 0x0);
	WREG32(mmTPC_PLL_DIV_SEL_2, 0x0);
	WREG32(mmTPC_PLL_DIV_SEL_3, 0x0);
}