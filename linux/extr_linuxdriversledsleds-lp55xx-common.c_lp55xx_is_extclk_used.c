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
struct lp55xx_chip {TYPE_1__* cl; struct clk* clk; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ LP55XX_CLK_32K ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 scalar_t__ clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

bool lp55xx_is_extclk_used(struct lp55xx_chip *chip)
{
	struct clk *clk;
	int err;

	clk = devm_clk_get(&chip->cl->dev, "32k_clk");
	if (IS_ERR(clk))
		goto use_internal_clk;

	err = clk_prepare_enable(clk);
	if (err)
		goto use_internal_clk;

	if (clk_get_rate(clk) != LP55XX_CLK_32K) {
		clk_disable_unprepare(clk);
		goto use_internal_clk;
	}

	dev_info(&chip->cl->dev, "%dHz external clock used\n",	LP55XX_CLK_32K);

	chip->clk = clk;
	return true;

use_internal_clk:
	dev_info(&chip->cl->dev, "internal clock used\n");
	return false;
}