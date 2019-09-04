#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ sfp_mod_absent; } ;

/* Variables and functions */
 int xgbe_phy_get_comm_ownership (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_put_comm_ownership (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_external_phy (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_mod_absent (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_parse_eeprom (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_phy_settings (struct xgbe_prv_data*) ; 
 int xgbe_phy_sfp_read_eeprom (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_reset (struct xgbe_phy_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_signals (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_sfp_detect(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	int ret;

	/* Reset the SFP signals and info */
	xgbe_phy_sfp_reset(phy_data);

	ret = xgbe_phy_get_comm_ownership(pdata);
	if (ret)
		return;

	/* Read the SFP signals and check for module presence */
	xgbe_phy_sfp_signals(pdata);
	if (phy_data->sfp_mod_absent) {
		xgbe_phy_sfp_mod_absent(pdata);
		goto put;
	}

	ret = xgbe_phy_sfp_read_eeprom(pdata);
	if (ret) {
		/* Treat any error as if there isn't an SFP plugged in */
		xgbe_phy_sfp_reset(phy_data);
		xgbe_phy_sfp_mod_absent(pdata);
		goto put;
	}

	xgbe_phy_sfp_parse_eeprom(pdata);

	xgbe_phy_sfp_external_phy(pdata);

put:
	xgbe_phy_sfp_phy_settings(pdata);

	xgbe_phy_put_comm_ownership(pdata);
}