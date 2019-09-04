#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_dsi_host {TYPE_1__* pdev; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/ * workqueue; } ;
struct mipi_dsi_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_tx_buf_free (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

void msm_dsi_host_destroy(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	DBG("");
	dsi_tx_buf_free(msm_host);
	if (msm_host->workqueue) {
		flush_workqueue(msm_host->workqueue);
		destroy_workqueue(msm_host->workqueue);
		msm_host->workqueue = NULL;
	}

	mutex_destroy(&msm_host->cmd_mutex);
	mutex_destroy(&msm_host->dev_mutex);

	pm_runtime_disable(&msm_host->pdev->dev);
}