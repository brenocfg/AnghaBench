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
typedef  int /*<<< orphan*/  u32 ;
struct mdfld_dsi_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int mdfld_dsi_get_panel_status (struct mdfld_dsi_config*,int,int /*<<< orphan*/ *,int) ; 

int mdfld_dsi_get_power_mode(struct mdfld_dsi_config *dsi_config, u32 *mode,
			bool hs)
{
	if (!dsi_config || !mode) {
		DRM_ERROR("Invalid parameter\n");
		return -EINVAL;
	}

	return mdfld_dsi_get_panel_status(dsi_config, 0x0a, mode, hs);
}