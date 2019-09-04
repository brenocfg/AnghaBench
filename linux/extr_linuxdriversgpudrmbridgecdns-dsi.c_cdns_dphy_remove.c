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
struct cdns_dphy {int /*<<< orphan*/  psm_clk; int /*<<< orphan*/  pll_ref_clk; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct cdns_dphy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cdns_dphy*) ; 

__attribute__((used)) static void cdns_dphy_remove(struct cdns_dphy *dphy)
{
	if (dphy->ops->remove)
		dphy->ops->remove(dphy);

	clk_put(dphy->pll_ref_clk);
	clk_put(dphy->psm_clk);
}