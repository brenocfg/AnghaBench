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
typedef  int /*<<< orphan*/  u32 ;
struct msm_dsi_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CMD_DMA_CTRL_LOW_POWER ; 
 int /*<<< orphan*/  REG_DSI_CMD_DMA_CTRL ; 
 int /*<<< orphan*/  dsi_read (struct msm_dsi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_set_tx_power_mode(int mode, struct msm_dsi_host *msm_host)
{
	u32 data;

	data = dsi_read(msm_host, REG_DSI_CMD_DMA_CTRL);

	if (mode == 0)
		data &= ~DSI_CMD_DMA_CTRL_LOW_POWER;
	else
		data |= DSI_CMD_DMA_CTRL_LOW_POWER;

	dsi_write(msm_host, REG_DSI_CMD_DMA_CTRL, data);
}