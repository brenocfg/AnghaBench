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
struct cdns_dphy {TYPE_1__* ops; int /*<<< orphan*/  psm_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_psm_div ) (struct cdns_dphy*,unsigned long) ;} ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int) ; 
 int EINVAL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cdns_dphy*,unsigned long) ; 

__attribute__((used)) static int cdns_dphy_setup_psm(struct cdns_dphy *dphy)
{
	unsigned long psm_clk_hz = clk_get_rate(dphy->psm_clk);
	unsigned long psm_div;

	if (!psm_clk_hz || psm_clk_hz > 100000000)
		return -EINVAL;

	psm_div = DIV_ROUND_CLOSEST(psm_clk_hz, 1000000);
	if (dphy->ops->set_psm_div)
		dphy->ops->set_psm_div(dphy, psm_div);

	return 0;
}