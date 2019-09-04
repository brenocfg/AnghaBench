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
struct dss_pll {int /*<<< orphan*/  cinfo; int /*<<< orphan*/  clkin; scalar_t__ regulator; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct dss_pll*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct dss_pll*) ; 

void dss_pll_disable(struct dss_pll *pll)
{
	pll->ops->disable(pll);

	if (pll->regulator)
		regulator_disable(pll->regulator);

	clk_disable_unprepare(pll->clkin);

	memset(&pll->cinfo, 0, sizeof(pll->cinfo));
}