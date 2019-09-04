#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_dsi_host {TYPE_1__* pdev; int /*<<< orphan*/  dma_cmd_ctrl_restore; struct msm_dsi_cfg_handler* cfg_hnd; } ;
struct msm_dsi_cfg_handler {TYPE_2__* ops; } ;
struct mipi_dsi_msg {int flags; } ;
struct mipi_dsi_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* link_clk_disable ) (struct msm_dsi_host*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_IRQ_MASK_CMD_DMA_DONE ; 
 int MIPI_DSI_MSG_USE_LPM ; 
 int /*<<< orphan*/  REG_DSI_CTRL ; 
 int /*<<< orphan*/  dsi_intr_ctrl (struct msm_dsi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_set_tx_power_mode (int,struct msm_dsi_host*) ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_dsi_host*) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

void msm_dsi_host_xfer_restore(struct mipi_dsi_host *host,
				const struct mipi_dsi_msg *msg)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const struct msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;

	dsi_intr_ctrl(msm_host, DSI_IRQ_MASK_CMD_DMA_DONE, 0);
	dsi_write(msm_host, REG_DSI_CTRL, msm_host->dma_cmd_ctrl_restore);

	if (!(msg->flags & MIPI_DSI_MSG_USE_LPM))
		dsi_set_tx_power_mode(1, msm_host);

	/* TODO: unvote for bus bandwidth */

	cfg_hnd->ops->link_clk_disable(msm_host);
	pm_runtime_put_autosuspend(&msm_host->pdev->dev);
}