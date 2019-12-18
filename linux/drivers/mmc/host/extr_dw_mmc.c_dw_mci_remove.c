#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dw_mci {int /*<<< orphan*/  biu_clk; int /*<<< orphan*/  ciu_clk; TYPE_2__* pdata; TYPE_1__* dma_ops; scalar_t__ use_dma; scalar_t__ slot; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  rstc; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* exit ) (struct dw_mci*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLKENA ; 
 int /*<<< orphan*/  CLKSRC ; 
 int /*<<< orphan*/  INTMASK ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINTSTS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_mci_cleanup_slot (scalar_t__) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dw_mci*) ; 

void dw_mci_remove(struct dw_mci *host)
{
	dev_dbg(host->dev, "remove slot\n");
	if (host->slot)
		dw_mci_cleanup_slot(host->slot);

	mci_writel(host, RINTSTS, 0xFFFFFFFF);
	mci_writel(host, INTMASK, 0); /* disable all mmc interrupt first */

	/* disable clock to CIU */
	mci_writel(host, CLKENA, 0);
	mci_writel(host, CLKSRC, 0);

	if (host->use_dma && host->dma_ops->exit)
		host->dma_ops->exit(host);

	if (!IS_ERR(host->pdata->rstc))
		reset_control_assert(host->pdata->rstc);

	clk_disable_unprepare(host->ciu_clk);
	clk_disable_unprepare(host->biu_clk);
}