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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bd_num; } ;
struct qtnf_pcie_pearl_state {int /*<<< orphan*/  pcie_reg_base; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HHBM_64BIT ; 
 int /*<<< orphan*/  HHBM_CONFIG_SOFT_RESET ; 
 int /*<<< orphan*/  PCIE_HHBM_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HHBM_Q_LIMIT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pearl_hhbm_init(struct qtnf_pcie_pearl_state *ps)
{
	u32 val;

	val = readl(PCIE_HHBM_CONFIG(ps->pcie_reg_base));
	val |= HHBM_CONFIG_SOFT_RESET;
	writel(val, PCIE_HHBM_CONFIG(ps->pcie_reg_base));
	usleep_range(50, 100);
	val &= ~HHBM_CONFIG_SOFT_RESET;
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	val |= HHBM_64BIT;
#endif
	writel(val, PCIE_HHBM_CONFIG(ps->pcie_reg_base));
	writel(ps->base.rx_bd_num, PCIE_HHBM_Q_LIMIT_REG(ps->pcie_reg_base));

	return 0;
}