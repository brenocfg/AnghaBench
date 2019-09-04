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
struct xgbe_hw_if {int /*<<< orphan*/  (* config_rx_coalesce ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* usec_to_riwt ) (struct xgbe_prv_data*,int /*<<< orphan*/ ) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_usecs; int /*<<< orphan*/  rx_riwt; struct xgbe_hw_if hw_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  XGMAC_INIT_DMA_RX_FRAMES ; 
 int /*<<< orphan*/  XGMAC_INIT_DMA_RX_USECS ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 

void xgbe_init_rx_coalesce(struct xgbe_prv_data *pdata)
{
	struct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPR("-->xgbe_init_rx_coalesce\n");

	pdata->rx_riwt = hw_if->usec_to_riwt(pdata, XGMAC_INIT_DMA_RX_USECS);
	pdata->rx_usecs = XGMAC_INIT_DMA_RX_USECS;
	pdata->rx_frames = XGMAC_INIT_DMA_RX_FRAMES;

	hw_if->config_rx_coalesce(pdata);

	DBGPR("<--xgbe_init_rx_coalesce\n");
}