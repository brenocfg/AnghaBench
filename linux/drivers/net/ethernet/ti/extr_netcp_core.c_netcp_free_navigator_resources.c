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
struct netcp_intf {int /*<<< orphan*/ * tx_pool; int /*<<< orphan*/ * tx_compl_q; int /*<<< orphan*/ ** rx_fdq; int /*<<< orphan*/ * rx_queue; int /*<<< orphan*/ * rx_pool; int /*<<< orphan*/ * rx_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int KNAV_DMA_FDQ_PER_CHAN ; 
 int /*<<< orphan*/  knav_dma_close_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knav_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knav_queue_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netcp_rxpool_free (struct netcp_intf*) ; 

__attribute__((used)) static void netcp_free_navigator_resources(struct netcp_intf *netcp)
{
	int i;

	if (netcp->rx_channel) {
		knav_dma_close_channel(netcp->rx_channel);
		netcp->rx_channel = NULL;
	}

	if (!IS_ERR_OR_NULL(netcp->rx_pool))
		netcp_rxpool_free(netcp);

	if (!IS_ERR_OR_NULL(netcp->rx_queue)) {
		knav_queue_close(netcp->rx_queue);
		netcp->rx_queue = NULL;
	}

	for (i = 0; i < KNAV_DMA_FDQ_PER_CHAN &&
	     !IS_ERR_OR_NULL(netcp->rx_fdq[i]) ; ++i) {
		knav_queue_close(netcp->rx_fdq[i]);
		netcp->rx_fdq[i] = NULL;
	}

	if (!IS_ERR_OR_NULL(netcp->tx_compl_q)) {
		knav_queue_close(netcp->tx_compl_q);
		netcp->tx_compl_q = NULL;
	}

	if (!IS_ERR_OR_NULL(netcp->tx_pool)) {
		knav_pool_destroy(netcp->tx_pool);
		netcp->tx_pool = NULL;
	}
}