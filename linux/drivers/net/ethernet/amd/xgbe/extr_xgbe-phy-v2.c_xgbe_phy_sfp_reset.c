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
struct xgbe_phy_data {int sfp_mod_absent; int /*<<< orphan*/  sfp_speed; int /*<<< orphan*/  sfp_cable; int /*<<< orphan*/  sfp_base; scalar_t__ sfp_tx_fault; scalar_t__ sfp_rx_los; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_SFP_BASE_UNKNOWN ; 
 int /*<<< orphan*/  XGBE_SFP_CABLE_UNKNOWN ; 
 int /*<<< orphan*/  XGBE_SFP_SPEED_UNKNOWN ; 

__attribute__((used)) static void xgbe_phy_sfp_reset(struct xgbe_phy_data *phy_data)
{
	phy_data->sfp_rx_los = 0;
	phy_data->sfp_tx_fault = 0;
	phy_data->sfp_mod_absent = 1;
	phy_data->sfp_base = XGBE_SFP_BASE_UNKNOWN;
	phy_data->sfp_cable = XGBE_SFP_CABLE_UNKNOWN;
	phy_data->sfp_speed = XGBE_SFP_SPEED_UNKNOWN;
}