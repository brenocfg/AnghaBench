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
struct TYPE_2__ {unsigned int (* set_gpio ) (struct xgbe_prv_data*,int /*<<< orphan*/ ) ;unsigned int (* clr_gpio ) (struct xgbe_prv_data*,int /*<<< orphan*/ ) ;} ;
struct xgbe_prv_data {TYPE_1__ hw_if; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int /*<<< orphan*/  mdio_reset_gpio; } ;

/* Variables and functions */
 unsigned int stub1 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_phy_int_mdio_reset(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int ret;

	ret = pdata->hw_if.set_gpio(pdata, phy_data->mdio_reset_gpio);
	if (ret)
		return ret;

	ret = pdata->hw_if.clr_gpio(pdata, phy_data->mdio_reset_gpio);

	return ret;
}