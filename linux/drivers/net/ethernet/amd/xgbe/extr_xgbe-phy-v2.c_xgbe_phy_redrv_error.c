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
struct xgbe_phy_data {scalar_t__ redrv_if; int redrv_model; int redrv_lane; int /*<<< orphan*/  redrv; } ;

/* Variables and functions */
 scalar_t__ XGBE_PHY_REDRV_IF_MAX ; 
#define  XGBE_PHY_REDRV_MODEL_4223 129 
#define  XGBE_PHY_REDRV_MODEL_4227 128 

__attribute__((used)) static bool xgbe_phy_redrv_error(struct xgbe_phy_data *phy_data)
{
	if (!phy_data->redrv)
		return false;

	if (phy_data->redrv_if >= XGBE_PHY_REDRV_IF_MAX)
		return true;

	switch (phy_data->redrv_model) {
	case XGBE_PHY_REDRV_MODEL_4223:
		if (phy_data->redrv_lane > 3)
			return true;
		break;
	case XGBE_PHY_REDRV_MODEL_4227:
		if (phy_data->redrv_lane > 1)
			return true;
		break;
	default:
		return true;
	}

	return false;
}