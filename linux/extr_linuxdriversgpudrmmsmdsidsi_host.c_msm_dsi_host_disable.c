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
struct msm_dsi_host {int enabled; int mode_flags; } ;
struct mipi_dsi_host {int dummy; } ;

/* Variables and functions */
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  dsi_op_mode_config (struct msm_dsi_host*,int,int) ; 
 int /*<<< orphan*/  dsi_sw_reset (struct msm_dsi_host*) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

int msm_dsi_host_disable(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	msm_host->enabled = false;
	dsi_op_mode_config(msm_host,
		!!(msm_host->mode_flags & MIPI_DSI_MODE_VIDEO), false);

	/* Since we have disabled INTF, the video engine won't stop so that
	 * the cmd engine will be blocked.
	 * Reset to disable video engine so that we can send off cmd.
	 */
	dsi_sw_reset(msm_host);

	return 0;
}