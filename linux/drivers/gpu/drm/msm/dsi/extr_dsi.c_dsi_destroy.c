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
struct msm_dsi {int /*<<< orphan*/  pdev; int /*<<< orphan*/ * host; int /*<<< orphan*/ * phy_dev; int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_dsi_host_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_dsi_manager_unregister (struct msm_dsi*) ; 
 int /*<<< orphan*/  platform_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_destroy(struct msm_dsi *msm_dsi)
{
	if (!msm_dsi)
		return;

	msm_dsi_manager_unregister(msm_dsi);

	if (msm_dsi->phy_dev) {
		put_device(msm_dsi->phy_dev);
		msm_dsi->phy = NULL;
		msm_dsi->phy_dev = NULL;
	}

	if (msm_dsi->host) {
		msm_dsi_host_destroy(msm_dsi->host);
		msm_dsi->host = NULL;
	}

	platform_set_drvdata(msm_dsi->pdev, NULL);
}