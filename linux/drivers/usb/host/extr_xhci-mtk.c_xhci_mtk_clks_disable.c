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
struct xhci_hcd_mtk {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  xhci_clk; int /*<<< orphan*/  mcu_clk; int /*<<< orphan*/  dma_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_mtk_clks_disable(struct xhci_hcd_mtk *mtk)
{
	clk_disable_unprepare(mtk->dma_clk);
	clk_disable_unprepare(mtk->mcu_clk);
	clk_disable_unprepare(mtk->xhci_clk);
	clk_disable_unprepare(mtk->sys_clk);
	clk_disable_unprepare(mtk->ref_clk);
}