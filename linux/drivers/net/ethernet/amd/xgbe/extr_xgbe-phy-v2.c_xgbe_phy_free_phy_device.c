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
struct xgbe_phy_data {int /*<<< orphan*/ * phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_device_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_device_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_phy_free_phy_device(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	if (phy_data->phydev) {
		phy_detach(phy_data->phydev);
		phy_device_remove(phy_data->phydev);
		phy_device_free(phy_data->phydev);
		phy_data->phydev = NULL;
	}
}