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
struct xgbe_prv_data {unsigned int rx_q_count; int /*<<< orphan*/  netdev; TYPE_1__* pfc; scalar_t__ ets; scalar_t__ pfc_rfa; int /*<<< orphan*/  pfcq; } ;
struct TYPE_2__ {scalar_t__ pfc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_RQOMR ; 
 int /*<<< orphan*/  RQS ; 
 int XGBE_MAX_QUEUES ; 
 unsigned int XGMAC_FIFO_UNIT ; 
 int /*<<< orphan*/  XGMAC_MTL_IOWRITE_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int XGMAC_PRIO_QUEUES (unsigned int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_info (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  xgbe_calculate_dcb_fifo (struct xgbe_prv_data*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  xgbe_calculate_equal_fifo (unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  xgbe_calculate_flow_control_threshold (struct xgbe_prv_data*,unsigned int*) ; 
 int /*<<< orphan*/  xgbe_config_flow_control_threshold (struct xgbe_prv_data*) ; 
 unsigned int xgbe_get_rx_fifo_size (struct xgbe_prv_data*) ; 
 unsigned int xgbe_set_nonprio_fifos (unsigned int,unsigned int,unsigned int*) ; 

__attribute__((used)) static void xgbe_config_rx_fifo_size(struct xgbe_prv_data *pdata)
{
	unsigned int fifo_size;
	unsigned int fifo[XGBE_MAX_QUEUES];
	unsigned int prio_queues;
	unsigned int i;

	/* Clear any DCB related fifo/queue information */
	memset(pdata->pfcq, 0, sizeof(pdata->pfcq));
	pdata->pfc_rfa = 0;

	fifo_size = xgbe_get_rx_fifo_size(pdata);
	prio_queues = XGMAC_PRIO_QUEUES(pdata->rx_q_count);

	/* Assign a minimum fifo to the non-VLAN priority queues */
	fifo_size = xgbe_set_nonprio_fifos(fifo_size, pdata->rx_q_count, fifo);

	if (pdata->pfc && pdata->ets)
		xgbe_calculate_dcb_fifo(pdata, fifo_size, fifo);
	else
		xgbe_calculate_equal_fifo(fifo_size, prio_queues, fifo);

	for (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, RQS, fifo[i]);

	xgbe_calculate_flow_control_threshold(pdata, fifo);
	xgbe_config_flow_control_threshold(pdata);

	if (pdata->pfc && pdata->ets && pdata->pfc->pfc_en) {
		netif_info(pdata, drv, pdata->netdev,
			   "%u Rx hardware queues\n", pdata->rx_q_count);
		for (i = 0; i < pdata->rx_q_count; i++)
			netif_info(pdata, drv, pdata->netdev,
				   "RxQ%u, %u byte fifo queue\n", i,
				   ((fifo[i] + 1) * XGMAC_FIFO_UNIT));
	} else {
		netif_info(pdata, drv, pdata->netdev,
			   "%u Rx hardware queues, %u byte fifo per queue\n",
			   pdata->rx_q_count,
			   ((fifo[0] + 1) * XGMAC_FIFO_UNIT));
	}
}