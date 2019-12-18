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
struct exynos_pcie {TYPE_1__* mem_res; } ;
struct TYPE_2__ {int /*<<< orphan*/  elbi_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CORE_RESET ; 
 int /*<<< orphan*/  PCIE_CORE_RESET_ENABLE ; 
 int /*<<< orphan*/  PCIE_NONSTICKY_RESET ; 
 int /*<<< orphan*/  PCIE_PWR_RESET ; 
 int /*<<< orphan*/  PCIE_STICKY_RESET ; 
 int /*<<< orphan*/  exynos_pcie_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pcie_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_pcie_assert_core_reset(struct exynos_pcie *ep)
{
	u32 val;

	val = exynos_pcie_readl(ep->mem_res->elbi_base, PCIE_CORE_RESET);
	val &= ~PCIE_CORE_RESET_ENABLE;
	exynos_pcie_writel(ep->mem_res->elbi_base, val, PCIE_CORE_RESET);
	exynos_pcie_writel(ep->mem_res->elbi_base, 0, PCIE_PWR_RESET);
	exynos_pcie_writel(ep->mem_res->elbi_base, 0, PCIE_STICKY_RESET);
	exynos_pcie_writel(ep->mem_res->elbi_base, 0, PCIE_NONSTICKY_RESET);
}