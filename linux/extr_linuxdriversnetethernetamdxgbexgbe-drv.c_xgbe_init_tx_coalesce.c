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
struct xgbe_hw_if {int /*<<< orphan*/  (* config_tx_coalesce ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_usecs; struct xgbe_hw_if hw_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  XGMAC_INIT_DMA_TX_FRAMES ; 
 int /*<<< orphan*/  XGMAC_INIT_DMA_TX_USECS ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 

void xgbe_init_tx_coalesce(struct xgbe_prv_data *pdata)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPR("-->xgbe_init_tx_coalesce\n");

	pdata->tx_usecs = XGMAC_INIT_DMA_TX_USECS;
	pdata->tx_frames = XGMAC_INIT_DMA_TX_FRAMES;

	hw_if->config_tx_coalesce(pdata);

	DBGPR("<--xgbe_init_tx_coalesce\n");
}