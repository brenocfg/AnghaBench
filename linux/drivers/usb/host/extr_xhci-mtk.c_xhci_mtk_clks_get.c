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
struct xhci_hcd_mtk {void* dma_clk; void* mcu_clk; void* ref_clk; void* xhci_clk; void* sys_clk; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_clk_get_optional (struct device*,char*) ; 

__attribute__((used)) static int xhci_mtk_clks_get(struct xhci_hcd_mtk *mtk)
{
	struct device *dev = mtk->dev;

	mtk->sys_clk = devm_clk_get(dev, "sys_ck");
	if (IS_ERR(mtk->sys_clk)) {
		dev_err(dev, "fail to get sys_ck\n");
		return PTR_ERR(mtk->sys_clk);
	}

	mtk->xhci_clk = devm_clk_get_optional(dev, "xhci_ck");
	if (IS_ERR(mtk->xhci_clk))
		return PTR_ERR(mtk->xhci_clk);

	mtk->ref_clk = devm_clk_get_optional(dev, "ref_ck");
	if (IS_ERR(mtk->ref_clk))
		return PTR_ERR(mtk->ref_clk);

	mtk->mcu_clk = devm_clk_get_optional(dev, "mcu_ck");
	if (IS_ERR(mtk->mcu_clk))
		return PTR_ERR(mtk->mcu_clk);

	mtk->dma_clk = devm_clk_get_optional(dev, "dma_ck");
	return PTR_ERR_OR_ZERO(mtk->dma_clk);
}