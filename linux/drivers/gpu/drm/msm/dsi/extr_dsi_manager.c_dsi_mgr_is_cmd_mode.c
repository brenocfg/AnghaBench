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
struct msm_dsi {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 unsigned long MIPI_DSI_MODE_VIDEO ; 
 unsigned long msm_dsi_host_get_mode_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dsi_mgr_is_cmd_mode(struct msm_dsi *msm_dsi)
{
	unsigned long host_flags = msm_dsi_host_get_mode_flags(msm_dsi->host);
	return !(host_flags & MIPI_DSI_MODE_VIDEO);
}