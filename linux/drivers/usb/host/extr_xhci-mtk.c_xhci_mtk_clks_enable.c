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
struct xhci_hcd_mtk {int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  xhci_clk; int /*<<< orphan*/  mcu_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int xhci_mtk_clks_enable(struct xhci_hcd_mtk *mtk)
{
	int ret;

	ret = clk_prepare_enable(mtk->ref_clk);
	if (ret) {
		dev_err(mtk->dev, "failed to enable ref_clk\n");
		goto ref_clk_err;
	}

	ret = clk_prepare_enable(mtk->sys_clk);
	if (ret) {
		dev_err(mtk->dev, "failed to enable sys_clk\n");
		goto sys_clk_err;
	}

	ret = clk_prepare_enable(mtk->xhci_clk);
	if (ret) {
		dev_err(mtk->dev, "failed to enable xhci_clk\n");
		goto xhci_clk_err;
	}

	ret = clk_prepare_enable(mtk->mcu_clk);
	if (ret) {
		dev_err(mtk->dev, "failed to enable mcu_clk\n");
		goto mcu_clk_err;
	}

	ret = clk_prepare_enable(mtk->dma_clk);
	if (ret) {
		dev_err(mtk->dev, "failed to enable dma_clk\n");
		goto dma_clk_err;
	}

	return 0;

dma_clk_err:
	clk_disable_unprepare(mtk->mcu_clk);
mcu_clk_err:
	clk_disable_unprepare(mtk->xhci_clk);
xhci_clk_err:
	clk_disable_unprepare(mtk->sys_clk);
sys_clk_err:
	clk_disable_unprepare(mtk->ref_clk);
ref_clk_err:
	return ret;
}