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
struct TYPE_2__ {scalar_t__ autoneg; int /*<<< orphan*/  speed; } ;
struct xgbe_prv_data {TYPE_1__ phy; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int xgbe_phy_get_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xgbe_phy_check_mode(struct xgbe_prv_data *pdata,
				enum xgbe_mode mode, bool advert)
{
	if (pdata->phy.autoneg == AUTONEG_ENABLE) {
		return advert;
	} else {
		enum xgbe_mode cur_mode;

		cur_mode = xgbe_phy_get_mode(pdata, pdata->phy.speed);
		if (cur_mode == mode)
			return true;
	}

	return false;
}