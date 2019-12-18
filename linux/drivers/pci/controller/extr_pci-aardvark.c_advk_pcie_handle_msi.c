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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct advk_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 scalar_t__ MSI_IRQ_NUM ; 
 scalar_t__ PCIE_ISR0_MSI_INT_PENDING ; 
 int /*<<< orphan*/  PCIE_ISR0_REG ; 
 int /*<<< orphan*/  PCIE_MSI_MASK_REG ; 
 int /*<<< orphan*/  PCIE_MSI_PAYLOAD_REG ; 
 int /*<<< orphan*/  PCIE_MSI_STATUS_REG ; 
 int advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advk_writel (struct advk_pcie*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 

__attribute__((used)) static void advk_pcie_handle_msi(struct advk_pcie *pcie)
{
	u32 msi_val, msi_mask, msi_status, msi_idx;
	u16 msi_data;

	msi_mask = advk_readl(pcie, PCIE_MSI_MASK_REG);
	msi_val = advk_readl(pcie, PCIE_MSI_STATUS_REG);
	msi_status = msi_val & ~msi_mask;

	for (msi_idx = 0; msi_idx < MSI_IRQ_NUM; msi_idx++) {
		if (!(BIT(msi_idx) & msi_status))
			continue;

		advk_writel(pcie, BIT(msi_idx), PCIE_MSI_STATUS_REG);
		msi_data = advk_readl(pcie, PCIE_MSI_PAYLOAD_REG) & 0xFF;
		generic_handle_irq(msi_data);
	}

	advk_writel(pcie, PCIE_ISR0_MSI_INT_PENDING,
		    PCIE_ISR0_REG);
}