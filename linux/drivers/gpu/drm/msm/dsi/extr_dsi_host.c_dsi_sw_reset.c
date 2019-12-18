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

/* Variables and functions */
 int DSI_CLK_CTRL_ENABLE_CLKS ; 
 int /*<<< orphan*/  DSI_RESET_TOGGLE_DELAY_MS ; 
 int /*<<< orphan*/  REG_DSI_CLK_CTRL ; 
 int /*<<< orphan*/  REG_DSI_RESET ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dsi_sw_reset(struct msm_dsi_host *msm_host)
{
	dsi_write(msm_host, REG_DSI_CLK_CTRL, DSI_CLK_CTRL_ENABLE_CLKS);
	wmb(); /* clocks need to be enabled before reset */

	dsi_write(msm_host, REG_DSI_RESET, 1);
	msleep(DSI_RESET_TOGGLE_DELAY_MS); /* make sure reset happen */
	dsi_write(msm_host, REG_DSI_RESET, 0);
}