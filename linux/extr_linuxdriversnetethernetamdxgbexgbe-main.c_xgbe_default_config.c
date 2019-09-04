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
struct xgbe_prv_data {int aal; int rd_osr_limit; int wr_osr_limit; int pause_autoneg; int tx_pause; int rx_pause; scalar_t__ power_down; int /*<<< orphan*/  phy_speed; int /*<<< orphan*/  rx_threshold; int /*<<< orphan*/  rx_sf_mode; int /*<<< orphan*/  tx_osp_mode; int /*<<< orphan*/  tx_threshold; int /*<<< orphan*/  tx_sf_mode; int /*<<< orphan*/  pbl; int /*<<< orphan*/  blen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  DMA_OSP_ENABLE ; 
 int /*<<< orphan*/  DMA_PBL_128 ; 
 int /*<<< orphan*/  DMA_SBMR_BLEN_64 ; 
 int /*<<< orphan*/  MTL_RSF_DISABLE ; 
 int /*<<< orphan*/  MTL_RX_THRESHOLD_64 ; 
 int /*<<< orphan*/  MTL_TSF_ENABLE ; 
 int /*<<< orphan*/  MTL_TX_THRESHOLD_64 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 

__attribute__((used)) static void xgbe_default_config(struct xgbe_prv_data *pdata)
{
	DBGPR("-->xgbe_default_config\n");

	pdata->blen = DMA_SBMR_BLEN_64;
	pdata->pbl = DMA_PBL_128;
	pdata->aal = 1;
	pdata->rd_osr_limit = 8;
	pdata->wr_osr_limit = 8;
	pdata->tx_sf_mode = MTL_TSF_ENABLE;
	pdata->tx_threshold = MTL_TX_THRESHOLD_64;
	pdata->tx_osp_mode = DMA_OSP_ENABLE;
	pdata->rx_sf_mode = MTL_RSF_DISABLE;
	pdata->rx_threshold = MTL_RX_THRESHOLD_64;
	pdata->pause_autoneg = 1;
	pdata->tx_pause = 1;
	pdata->rx_pause = 1;
	pdata->phy_speed = SPEED_UNKNOWN;
	pdata->power_down = 0;

	DBGPR("<--xgbe_default_config\n");
}