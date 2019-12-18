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
struct msm_dsi_manager {int /*<<< orphan*/ ** dsi; } ;
struct msm_dsi {size_t id; scalar_t__ host; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_dsi_host_unregister (scalar_t__) ; 
 struct msm_dsi_manager msm_dsim_glb ; 

void msm_dsi_manager_unregister(struct msm_dsi *msm_dsi)
{
	struct msm_dsi_manager *msm_dsim = &msm_dsim_glb;

	if (msm_dsi->host)
		msm_dsi_host_unregister(msm_dsi->host);

	if (msm_dsi->id >= 0)
		msm_dsim->dsi[msm_dsi->id] = NULL;
}