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
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_stop ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {TYPE_1__ i2c_if; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_cdr_track (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_free_phy_device (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_power_off (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_mod_absent (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_reset (struct xgbe_phy_data*) ; 

__attribute__((used)) static void xgbe_phy_stop(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	/* If we have an external PHY, free it */
	xgbe_phy_free_phy_device(pdata);

	/* Reset SFP data */
	xgbe_phy_sfp_reset(phy_data);
	xgbe_phy_sfp_mod_absent(pdata);

	/* Reset CDR support */
	xgbe_phy_cdr_track(pdata);

	/* Power off the PHY */
	xgbe_phy_power_off(pdata);

	/* Stop the I2C controller */
	pdata->i2c_if.i2c_stop(pdata);
}