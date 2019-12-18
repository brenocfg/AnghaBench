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
struct xgbe_phy_data {int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_exit(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	/* Unregister for driving external PHYs */
	mdiobus_unregister(phy_data->mii);
}