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
struct cdns_dphy_cfg {int dummy; } ;
struct cdns_dphy {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_pll_cfg ) (struct cdns_dphy*,struct cdns_dphy_cfg const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cdns_dphy*,struct cdns_dphy_cfg const*) ; 

__attribute__((used)) static void cdns_dphy_set_pll_cfg(struct cdns_dphy *dphy,
				  const struct cdns_dphy_cfg *cfg)
{
	if (dphy->ops->set_pll_cfg)
		dphy->ops->set_pll_cfg(dphy, cfg);
}