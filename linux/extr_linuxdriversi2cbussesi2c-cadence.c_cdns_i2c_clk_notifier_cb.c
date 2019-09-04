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
struct notifier_block {int dummy; } ;
struct clk_notifier_data {unsigned long new_rate; unsigned long old_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct cdns_i2c {unsigned long i2c_clk; unsigned long input_clk; TYPE_2__ adap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ABORT_RATE_CHANGE 130 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int NOTIFY_STOP ; 
#define  POST_RATE_CHANGE 129 
#define  PRE_RATE_CHANGE 128 
 int cdns_i2c_calc_divs (unsigned long*,unsigned long,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  cdns_i2c_setclk (unsigned long,struct cdns_i2c*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 struct cdns_i2c* to_cdns_i2c (struct notifier_block*) ; 

__attribute__((used)) static int cdns_i2c_clk_notifier_cb(struct notifier_block *nb, unsigned long
		event, void *data)
{
	struct clk_notifier_data *ndata = data;
	struct cdns_i2c *id = to_cdns_i2c(nb);

	if (pm_runtime_suspended(id->dev))
		return NOTIFY_OK;

	switch (event) {
	case PRE_RATE_CHANGE:
	{
		unsigned long input_clk = ndata->new_rate;
		unsigned long fscl = id->i2c_clk;
		unsigned int div_a, div_b;
		int ret;

		ret = cdns_i2c_calc_divs(&fscl, input_clk, &div_a, &div_b);
		if (ret) {
			dev_warn(id->adap.dev.parent,
					"clock rate change rejected\n");
			return NOTIFY_STOP;
		}

		/* scale up */
		if (ndata->new_rate > ndata->old_rate)
			cdns_i2c_setclk(ndata->new_rate, id);

		return NOTIFY_OK;
	}
	case POST_RATE_CHANGE:
		id->input_clk = ndata->new_rate;
		/* scale down */
		if (ndata->new_rate < ndata->old_rate)
			cdns_i2c_setclk(ndata->new_rate, id);
		return NOTIFY_OK;
	case ABORT_RATE_CHANGE:
		/* scale up */
		if (ndata->new_rate > ndata->old_rate)
			cdns_i2c_setclk(ndata->old_rate, id);
		return NOTIFY_OK;
	default:
		return NOTIFY_DONE;
	}
}