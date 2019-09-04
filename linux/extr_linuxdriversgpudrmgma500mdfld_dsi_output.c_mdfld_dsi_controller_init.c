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
struct mdfld_dsi_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  mdfld_dsi_dpi_controller_init (struct mdfld_dsi_config*,int) ; 

void mdfld_dsi_controller_init(struct mdfld_dsi_config *dsi_config, int pipe)
{
	if (!dsi_config || ((pipe != 0) && (pipe != 2))) {
		DRM_ERROR("Invalid parameters\n");
		return;
	}

	mdfld_dsi_dpi_controller_init(dsi_config, pipe);
}