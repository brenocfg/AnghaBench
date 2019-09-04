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
struct msm_dsi_host {int /*<<< orphan*/  byte_clk; int /*<<< orphan*/  esc_clk; int /*<<< orphan*/  src_clk; int /*<<< orphan*/  pixel_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

void dsi_link_clk_disable_v2(struct msm_dsi_host *msm_host)
{
	clk_disable_unprepare(msm_host->pixel_clk);
	clk_disable_unprepare(msm_host->src_clk);
	clk_disable_unprepare(msm_host->esc_clk);
	clk_disable_unprepare(msm_host->byte_clk);
}