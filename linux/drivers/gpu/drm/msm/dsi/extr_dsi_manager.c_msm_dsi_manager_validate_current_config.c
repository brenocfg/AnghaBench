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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int IS_DUAL_DSI () ; 
 int /*<<< orphan*/  IS_MASTER_DSI_LINK (int /*<<< orphan*/ ) ; 

bool msm_dsi_manager_validate_current_config(u8 id)
{
	bool is_dual_dsi = IS_DUAL_DSI();

	/*
	 * For dual DSI, we only have one drm panel. For this
	 * use case, we register only one bridge/connector.
	 * Skip bridge/connector initialisation if it is
	 * slave-DSI for dual DSI configuration.
	 */
	if (is_dual_dsi && !IS_MASTER_DSI_LINK(id)) {
		DBG("Skip bridge registration for slave DSI->id: %d\n", id);
		return false;
	}
	return true;
}