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
struct resources {struct clk** clock; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; TYPE_1__* devdata; struct resources resources; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int clks_count; int /*<<< orphan*/ * clks; } ;

/* Variables and functions */
 scalar_t__ GPMI_IS_MX6 (struct gpmi_nand_data*) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpmi_get_clks(struct gpmi_nand_data *this)
{
	struct resources *r = &this->resources;
	struct clk *clk;
	int err, i;

	for (i = 0; i < this->devdata->clks_count; i++) {
		clk = devm_clk_get(this->dev, this->devdata->clks[i]);
		if (IS_ERR(clk)) {
			err = PTR_ERR(clk);
			goto err_clock;
		}

		r->clock[i] = clk;
	}

	if (GPMI_IS_MX6(this))
		/*
		 * Set the default value for the gpmi clock.
		 *
		 * If you want to use the ONFI nand which is in the
		 * Synchronous Mode, you should change the clock as you need.
		 */
		clk_set_rate(r->clock[0], 22000000);

	return 0;

err_clock:
	dev_dbg(this->dev, "failed in finding the clocks.\n");
	return err;
}