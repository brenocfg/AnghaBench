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
struct netcp_intf {scalar_t__ rx_pool_size; int /*<<< orphan*/ * rx_pool; int /*<<< orphan*/  ndev_dev; int /*<<< orphan*/ * rx_fdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int KNAV_DMA_FDQ_PER_CHAN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ knav_pool_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knav_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netcp_free_rx_buf (struct netcp_intf*,int) ; 

__attribute__((used)) static void netcp_rxpool_free(struct netcp_intf *netcp)
{
	int i;

	for (i = 0; i < KNAV_DMA_FDQ_PER_CHAN &&
	     !IS_ERR_OR_NULL(netcp->rx_fdq[i]); i++)
		netcp_free_rx_buf(netcp, i);

	if (knav_pool_count(netcp->rx_pool) != netcp->rx_pool_size)
		dev_err(netcp->ndev_dev, "Lost Rx (%d) descriptors\n",
			netcp->rx_pool_size - knav_pool_count(netcp->rx_pool));

	knav_pool_destroy(netcp->rx_pool);
	netcp->rx_pool = NULL;
}