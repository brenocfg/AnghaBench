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
struct platform_device {int dummy; } ;
struct msm_dsi_host {int /*<<< orphan*/  cfg_hnd; } ;
struct msm_dsi {struct mipi_dsi_host* host; } ;
struct mipi_dsi_host {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int dsi_bus_clk_enable (struct msm_dsi_host*) ; 
 struct msm_dsi* platform_get_drvdata (struct platform_device*) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int msm_dsi_runtime_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct msm_dsi *msm_dsi = platform_get_drvdata(pdev);
	struct mipi_dsi_host *host = msm_dsi->host;
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	if (!msm_host->cfg_hnd)
		return 0;

	return dsi_bus_clk_enable(msm_host);
}