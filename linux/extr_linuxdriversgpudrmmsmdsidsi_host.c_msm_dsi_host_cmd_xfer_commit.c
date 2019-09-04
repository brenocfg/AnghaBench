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
typedef  int u32 ;
struct msm_dsi_host {int dummy; } ;
struct mipi_dsi_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DSI_DMA_BASE ; 
 int /*<<< orphan*/  REG_DSI_DMA_LEN ; 
 int /*<<< orphan*/  REG_DSI_TRIG_DMA ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  wmb () ; 

void msm_dsi_host_cmd_xfer_commit(struct mipi_dsi_host *host, u32 dma_base,
				  u32 len)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_write(msm_host, REG_DSI_DMA_BASE, dma_base);
	dsi_write(msm_host, REG_DSI_DMA_LEN, len);
	dsi_write(msm_host, REG_DSI_TRIG_DMA, 1);

	/* Make sure trigger happens */
	wmb();
}