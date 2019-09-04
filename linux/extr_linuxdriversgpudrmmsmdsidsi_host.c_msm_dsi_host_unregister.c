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
struct msm_dsi_host {int registered; } ;
struct mipi_dsi_host {int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipi_dsi_host_unregister (struct mipi_dsi_host*) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

void msm_dsi_host_unregister(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	if (msm_host->registered) {
		mipi_dsi_host_unregister(host);
		host->dev = NULL;
		host->ops = NULL;
		msm_host->registered = false;
	}
}