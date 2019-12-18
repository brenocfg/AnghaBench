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
struct xgbe_phy_data {int sfp_mod_absent; int /*<<< orphan*/  sfp_eeprom; scalar_t__ sfp_phy_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgbe_phy_free_phy_device (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_sfp_mod_absent(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_free_phy_device(pdata);

	phy_data->sfp_mod_absent = 1;
	phy_data->sfp_phy_avail = 0;
	memset(&phy_data->sfp_eeprom, 0, sizeof(phy_data->sfp_eeprom));
}