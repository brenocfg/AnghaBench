#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* enable_rx ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* disable_rx ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; TYPE_1__ hw_if; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_DOWN ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_config_flow_control (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_config_rx_fifo_size (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_config_dcb_pfc(struct xgbe_prv_data *pdata)
{
	if (!test_bit(XGBE_DOWN, &pdata->dev_state)) {
		/* Just stop the Tx queues while Rx fifo is changed */
		netif_tx_stop_all_queues(pdata->netdev);

		/* Suspend Rx so that fifo's can be adjusted */
		pdata->hw_if.disable_rx(pdata);
	}

	xgbe_config_rx_fifo_size(pdata);
	xgbe_config_flow_control(pdata);

	if (!test_bit(XGBE_DOWN, &pdata->dev_state)) {
		/* Resume Rx */
		pdata->hw_if.enable_rx(pdata);

		/* Resume Tx queues */
		netif_tx_start_all_queues(pdata->netdev);
	}
}