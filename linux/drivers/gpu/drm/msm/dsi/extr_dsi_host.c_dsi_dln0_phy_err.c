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
struct msm_dsi_host {int /*<<< orphan*/  err_work_state; } ;

/* Variables and functions */
 int DSI_DLN0_PHY_ERR_DLN0_ERR_CONTENTION_LP0 ; 
 int DSI_DLN0_PHY_ERR_DLN0_ERR_CONTENTION_LP1 ; 
 int DSI_DLN0_PHY_ERR_DLN0_ERR_CONTROL ; 
 int DSI_DLN0_PHY_ERR_DLN0_ERR_ESC ; 
 int DSI_DLN0_PHY_ERR_DLN0_ERR_SYNC_ESC ; 
 int /*<<< orphan*/  DSI_ERR_STATE_DLN0_PHY ; 
 int /*<<< orphan*/  REG_DSI_DLN0_PHY_ERR ; 
 int dsi_read (struct msm_dsi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct msm_dsi_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dsi_dln0_phy_err(struct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_read(msm_host, REG_DSI_DLN0_PHY_ERR);

	if (status & (DSI_DLN0_PHY_ERR_DLN0_ERR_ESC |
			DSI_DLN0_PHY_ERR_DLN0_ERR_SYNC_ESC |
			DSI_DLN0_PHY_ERR_DLN0_ERR_CONTROL |
			DSI_DLN0_PHY_ERR_DLN0_ERR_CONTENTION_LP0 |
			DSI_DLN0_PHY_ERR_DLN0_ERR_CONTENTION_LP1)) {
		dsi_write(msm_host, REG_DSI_DLN0_PHY_ERR, status);
		msm_host->err_work_state |= DSI_ERR_STATE_DLN0_PHY;
	}
}