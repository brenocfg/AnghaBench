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
struct dss_pll {int /*<<< orphan*/  clkin; scalar_t__ regulator; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable ) (struct dss_pll*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int stub1 (struct dss_pll*) ; 

int dss_pll_enable(struct dss_pll *pll)
{
	int r;

	r = clk_prepare_enable(pll->clkin);
	if (r)
		return r;

	if (pll->regulator) {
		r = regulator_enable(pll->regulator);
		if (r)
			goto err_reg;
	}

	r = pll->ops->enable(pll);
	if (r)
		goto err_enable;

	return 0;

err_enable:
	if (pll->regulator)
		regulator_disable(pll->regulator);
err_reg:
	clk_disable_unprepare(pll->clkin);
	return r;
}