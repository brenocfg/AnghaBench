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
struct msm_dsi_host {scalar_t__ byte_clk; scalar_t__ byte_intf_clk; scalar_t__ pixel_clk; scalar_t__ esc_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 

void dsi_link_clk_disable_6g(struct msm_dsi_host *msm_host)
{
	clk_disable_unprepare(msm_host->esc_clk);
	clk_disable_unprepare(msm_host->pixel_clk);
	if (msm_host->byte_intf_clk)
		clk_disable_unprepare(msm_host->byte_intf_clk);
	clk_disable_unprepare(msm_host->byte_clk);
}