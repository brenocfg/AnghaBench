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
struct bnx2x_phy {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833 ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834 ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858 ; 

__attribute__((used)) static int bnx2x_is_8483x_8485x(struct bnx2x_phy *phy)
{
	return ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833) ||
		(phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834) ||
		(phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858));
}