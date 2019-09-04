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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ xgbe_phy_belfuse_phy_quirks (struct xgbe_prv_data*) ; 
 scalar_t__ xgbe_phy_finisar_phy_quirks (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_external_phy_quirks(struct xgbe_prv_data *pdata)
{
	if (xgbe_phy_belfuse_phy_quirks(pdata))
		return;

	if (xgbe_phy_finisar_phy_quirks(pdata))
		return;
}