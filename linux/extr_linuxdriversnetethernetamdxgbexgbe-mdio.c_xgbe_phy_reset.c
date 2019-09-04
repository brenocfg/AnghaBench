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
struct TYPE_3__ {int (* reset ) (struct xgbe_prv_data*) ;} ;
struct TYPE_4__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {TYPE_2__ phy_if; } ;

/* Variables and functions */
 int stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_clear_interrupts_all (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_disable_all (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_reset(struct xgbe_prv_data *pdata)
{
	int ret;

	ret = pdata->phy_if.phy_impl.reset(pdata);
	if (ret)
		return ret;

	/* Disable auto-negotiation for now */
	xgbe_an_disable_all(pdata);

	/* Clear auto-negotiation interrupts */
	xgbe_an_clear_interrupts_all(pdata);

	return 0;
}