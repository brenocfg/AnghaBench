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
struct msm_dsi_host {int /*<<< orphan*/  err_work; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_IRQ_MASK_ERROR ; 
 int /*<<< orphan*/  dsi_ack_err_status (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  dsi_clk_status (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  dsi_dln0_phy_err (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  dsi_fifo_status (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  dsi_intr_ctrl (struct msm_dsi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_status (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  dsi_timeout_status (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsi_error(struct msm_dsi_host *msm_host)
{
	/* disable dsi error interrupt */
	dsi_intr_ctrl(msm_host, DSI_IRQ_MASK_ERROR, 0);

	dsi_clk_status(msm_host);
	dsi_fifo_status(msm_host);
	dsi_ack_err_status(msm_host);
	dsi_timeout_status(msm_host);
	dsi_status(msm_host);
	dsi_dln0_phy_err(msm_host);

	queue_work(msm_host->workqueue, &msm_host->err_work);
}