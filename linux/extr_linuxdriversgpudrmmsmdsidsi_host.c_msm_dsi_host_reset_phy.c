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
struct msm_dsi_host {int dummy; } ;
struct mipi_dsi_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  DSI_PHY_RESET_RESET ; 
 int /*<<< orphan*/  REG_DSI_PHY_RESET ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

void msm_dsi_host_reset_phy(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	DBG("");
	dsi_write(msm_host, REG_DSI_PHY_RESET, DSI_PHY_RESET_RESET);
	/* Make sure fully reset */
	wmb();
	udelay(1000);
	dsi_write(msm_host, REG_DSI_PHY_RESET, 0);
	udelay(100);
}