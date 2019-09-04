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
struct dsi_data {struct clk* dss_clk; int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dsi_get_clocks(struct dsi_data *dsi)
{
	struct clk *clk;

	clk = devm_clk_get(dsi->dev, "fck");
	if (IS_ERR(clk)) {
		DSSERR("can't get fck\n");
		return PTR_ERR(clk);
	}

	dsi->dss_clk = clk;

	return 0;
}