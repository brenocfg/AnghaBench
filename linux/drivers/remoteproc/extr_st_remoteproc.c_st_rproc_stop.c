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
struct st_rproc {int /*<<< orphan*/  clk; int /*<<< orphan*/  pwr_reset; TYPE_1__* config; int /*<<< orphan*/  sw_reset; } ;
struct rproc {int /*<<< orphan*/  dev; struct st_rproc* priv; } ;
struct TYPE_2__ {scalar_t__ pwr_reset; scalar_t__ sw_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_rproc_stop(struct rproc *rproc)
{
	struct st_rproc *ddata = rproc->priv;
	int sw_err = 0, pwr_err = 0;

	if (ddata->config->sw_reset) {
		sw_err = reset_control_assert(ddata->sw_reset);
		if (sw_err)
			dev_err(&rproc->dev, "Failed to assert S/W Reset\n");
	}

	if (ddata->config->pwr_reset) {
		pwr_err = reset_control_assert(ddata->pwr_reset);
		if (pwr_err)
			dev_err(&rproc->dev, "Failed to assert Power Reset\n");
	}

	clk_disable(ddata->clk);

	return sw_err ?: pwr_err;
}