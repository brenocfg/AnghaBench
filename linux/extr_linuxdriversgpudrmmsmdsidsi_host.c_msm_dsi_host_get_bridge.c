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
struct msm_dsi_host {int /*<<< orphan*/  device_node; } ;
struct mipi_dsi_host {int dummy; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct drm_bridge* of_drm_find_bridge (int /*<<< orphan*/ ) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

struct drm_bridge *msm_dsi_host_get_bridge(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	return of_drm_find_bridge(msm_host->device_node);
}