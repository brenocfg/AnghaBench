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
struct arasan_cf_pdata {unsigned int cf_if_clk; } ;
struct arasan_cf_dev {TYPE_1__* host; scalar_t__ vbase; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DETECT_IRQ ; 
 unsigned int CFHOST_ENB ; 
 unsigned int CF_IF_CLK_166M ; 
 unsigned int CF_IF_CLK_200M ; 
 scalar_t__ CLK_CFG ; 
 scalar_t__ OP_MODE ; 
 unsigned int TRUE_IDE_MODE ; 
 int /*<<< orphan*/  cf_ginterrupt_enable (struct arasan_cf_dev*,int) ; 
 int /*<<< orphan*/  cf_interrupt_enable (struct arasan_cf_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct arasan_cf_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int cf_init(struct arasan_cf_dev *acdev)
{
	struct arasan_cf_pdata *pdata = dev_get_platdata(acdev->host->dev);
	unsigned int if_clk;
	unsigned long flags;
	int ret = 0;

	ret = clk_prepare_enable(acdev->clk);
	if (ret) {
		dev_dbg(acdev->host->dev, "clock enable failed");
		return ret;
	}

	ret = clk_set_rate(acdev->clk, 166000000);
	if (ret) {
		dev_warn(acdev->host->dev, "clock set rate failed");
		clk_disable_unprepare(acdev->clk);
		return ret;
	}

	spin_lock_irqsave(&acdev->host->lock, flags);
	/* configure CF interface clock */
	/* TODO: read from device tree */
	if_clk = CF_IF_CLK_166M;
	if (pdata && pdata->cf_if_clk <= CF_IF_CLK_200M)
		if_clk = pdata->cf_if_clk;

	writel(if_clk, acdev->vbase + CLK_CFG);

	writel(TRUE_IDE_MODE | CFHOST_ENB, acdev->vbase + OP_MODE);
	cf_interrupt_enable(acdev, CARD_DETECT_IRQ, 1);
	cf_ginterrupt_enable(acdev, 1);
	spin_unlock_irqrestore(&acdev->host->lock, flags);

	return ret;
}