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
struct msm_dsi_host {int /*<<< orphan*/  hpd_work; int /*<<< orphan*/  workqueue; scalar_t__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/ * device_node; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

__attribute__((used)) static int dsi_host_detach(struct mipi_dsi_host *host,
					struct mipi_dsi_device *dsi)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	msm_host->device_node = NULL;

	DBG("id=%d", msm_host->id);
	if (msm_host->dev)
		queue_work(msm_host->workqueue, &msm_host->hpd_work);

	return 0;
}