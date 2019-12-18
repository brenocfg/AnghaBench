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
struct asm9260_wdt_priv {unsigned long wdt_freq; int /*<<< orphan*/  dev; void* clk; void* clk_ahb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_FREQ ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  asm9260_clk_disable_unprepare ; 
 unsigned long clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int clk_set_rate (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int asm9260_wdt_get_dt_clks(struct asm9260_wdt_priv *priv)
{
	int err;
	unsigned long clk;

	priv->clk = devm_clk_get(priv->dev, "mod");
	if (IS_ERR(priv->clk)) {
		dev_err(priv->dev, "Failed to get \"mod\" clk\n");
		return PTR_ERR(priv->clk);
	}

	/* configure AHB clock */
	priv->clk_ahb = devm_clk_get(priv->dev, "ahb");
	if (IS_ERR(priv->clk_ahb)) {
		dev_err(priv->dev, "Failed to get \"ahb\" clk\n");
		return PTR_ERR(priv->clk_ahb);
	}

	err = clk_prepare_enable(priv->clk_ahb);
	if (err) {
		dev_err(priv->dev, "Failed to enable ahb_clk!\n");
		return err;
	}
	err = devm_add_action_or_reset(priv->dev,
				       asm9260_clk_disable_unprepare,
				       priv->clk_ahb);
	if (err)
		return err;

	err = clk_set_rate(priv->clk, CLOCK_FREQ);
	if (err) {
		dev_err(priv->dev, "Failed to set rate!\n");
		return err;
	}

	err = clk_prepare_enable(priv->clk);
	if (err) {
		dev_err(priv->dev, "Failed to enable clk!\n");
		return err;
	}
	err = devm_add_action_or_reset(priv->dev,
				       asm9260_clk_disable_unprepare,
				       priv->clk);
	if (err)
		return err;

	/* wdt has internal divider */
	clk = clk_get_rate(priv->clk);
	if (!clk) {
		dev_err(priv->dev, "Failed, clk is 0!\n");
		return -EINVAL;
	}

	priv->wdt_freq = clk / 2;

	return 0;
}