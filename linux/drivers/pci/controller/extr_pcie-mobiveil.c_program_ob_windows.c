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
struct mobiveil_pcie {int apio_wins; int /*<<< orphan*/  ob_wins_configured; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AXI_WINDOW_ALIGN_MASK ; 
 int /*<<< orphan*/  PAB_AXI_AMAP_AXI_WIN (int) ; 
 int /*<<< orphan*/  PAB_AXI_AMAP_CTRL (int) ; 
 int /*<<< orphan*/  PAB_AXI_AMAP_PEX_WIN_H (int) ; 
 int /*<<< orphan*/  PAB_AXI_AMAP_PEX_WIN_L (int) ; 
 int /*<<< orphan*/  PAB_EXT_AXI_AMAP_AXI_WIN (int) ; 
 int /*<<< orphan*/  PAB_EXT_AXI_AMAP_SIZE (int) ; 
 int WIN_ENABLE_SHIFT ; 
 int WIN_SIZE_MASK ; 
 int WIN_TYPE_MASK ; 
 int WIN_TYPE_SHIFT ; 
 int csr_readl (struct mobiveil_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_writel (struct mobiveil_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void program_ob_windows(struct mobiveil_pcie *pcie, int win_num,
			       u64 cpu_addr, u64 pci_addr, u32 type, u64 size)
{
	u32 value;
	u64 size64 = ~(size - 1);

	if (win_num >= pcie->apio_wins) {
		dev_err(&pcie->pdev->dev,
			"ERROR: max outbound windows reached !\n");
		return;
	}

	/*
	 * program Enable Bit to 1, Type Bit to (00) base 2, AXI Window Size Bit
	 * to 4 KB in PAB_AXI_AMAP_CTRL register
	 */
	value = csr_readl(pcie, PAB_AXI_AMAP_CTRL(win_num));
	value &= ~(WIN_TYPE_MASK << WIN_TYPE_SHIFT | WIN_SIZE_MASK);
	value |= 1 << WIN_ENABLE_SHIFT | type << WIN_TYPE_SHIFT |
		 (lower_32_bits(size64) & WIN_SIZE_MASK);
	csr_writel(pcie, value, PAB_AXI_AMAP_CTRL(win_num));

	csr_writel(pcie, upper_32_bits(size64), PAB_EXT_AXI_AMAP_SIZE(win_num));

	/*
	 * program AXI window base with appropriate value in
	 * PAB_AXI_AMAP_AXI_WIN0 register
	 */
	csr_writel(pcie, lower_32_bits(cpu_addr) & (~AXI_WINDOW_ALIGN_MASK),
		   PAB_AXI_AMAP_AXI_WIN(win_num));
	csr_writel(pcie, upper_32_bits(cpu_addr),
		   PAB_EXT_AXI_AMAP_AXI_WIN(win_num));

	csr_writel(pcie, lower_32_bits(pci_addr),
		   PAB_AXI_AMAP_PEX_WIN_L(win_num));
	csr_writel(pcie, upper_32_bits(pci_addr),
		   PAB_AXI_AMAP_PEX_WIN_H(win_num));

	pcie->ob_wins_configured++;
}