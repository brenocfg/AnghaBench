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
struct msm_dsi_host {int mode_flags; int enabled; } ;
struct mipi_dsi_host {int dummy; } ;

/* Variables and functions */
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  dsi_op_mode_config (struct msm_dsi_host*,int,int) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

int msm_dsi_host_enable(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_op_mode_config(msm_host,
		!!(msm_host->mode_flags & MIPI_DSI_MODE_VIDEO), true);

	/* TODO: clock should be turned off for command mode,
	 * and only turned on before MDP START.
	 * This part of code should be enabled once mdp driver support it.
	 */
	/* if (msm_panel->mode == MSM_DSI_CMD_MODE) {
	 *	dsi_link_clk_disable(msm_host);
	 *	pm_runtime_put_autosuspend(&msm_host->pdev->dev);
	 * }
	 */
	msm_host->enabled = true;
	return 0;
}