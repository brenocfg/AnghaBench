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
typedef  int u64 ;
typedef  int u32 ;
struct mobiveil_pcie {int ppio_wins; int /*<<< orphan*/  ib_wins_configured; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMAP_CTRL_EN_SHIFT ; 
 int AMAP_CTRL_TYPE_MASK ; 
 int AMAP_CTRL_TYPE_SHIFT ; 
 int /*<<< orphan*/  PAB_EXT_PEX_AMAP_AXI_WIN (int) ; 
 int /*<<< orphan*/  PAB_EXT_PEX_AMAP_SIZEN (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_AXI_WIN (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_CTRL (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_PEX_WIN_H (int) ; 
 int /*<<< orphan*/  PAB_PEX_AMAP_PEX_WIN_L (int) ; 
 int WIN_SIZE_MASK ; 
 int csr_readl (struct mobiveil_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_writel (struct mobiveil_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void program_ib_windows(struct mobiveil_pcie *pcie, int win_num,
			       u64 cpu_addr, u64 pci_addr, u32 type, u64 size)
{
	u32 value;
	u64 size64 = ~(size - 1);

	if (win_num >= pcie->ppio_wins) {
		dev_err(&pcie->pdev->dev,
			"ERROR: max inbound windows reached !\n");
		return;
	}

	value = csr_readl(pcie, PAB_PEX_AMAP_CTRL(win_num));
	value &= ~(AMAP_CTRL_TYPE_MASK << AMAP_CTRL_TYPE_SHIFT | WIN_SIZE_MASK);
	value |= type << AMAP_CTRL_TYPE_SHIFT | 1 << AMAP_CTRL_EN_SHIFT |
		 (lower_32_bits(size64) & WIN_SIZE_MASK);
	csr_writel(pcie, value, PAB_PEX_AMAP_CTRL(win_num));

	csr_writel(pcie, upper_32_bits(size64),
		   PAB_EXT_PEX_AMAP_SIZEN(win_num));

	csr_writel(pcie, lower_32_bits(cpu_addr),
		   PAB_PEX_AMAP_AXI_WIN(win_num));
	csr_writel(pcie, upper_32_bits(cpu_addr),
		   PAB_EXT_PEX_AMAP_AXI_WIN(win_num));

	csr_writel(pcie, lower_32_bits(pci_addr),
		   PAB_PEX_AMAP_PEX_WIN_L(win_num));
	csr_writel(pcie, upper_32_bits(pci_addr),
		   PAB_PEX_AMAP_PEX_WIN_H(win_num));

	pcie->ib_wins_configured++;
}