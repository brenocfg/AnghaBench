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
struct xgbe_prv_data {unsigned int channel_count; struct xgbe_channel** channel; } ;
struct xgbe_channel {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  xgbe_free_ring (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_free_ring_resources(struct xgbe_prv_data *pdata)
{
	struct xgbe_channel *channel;
	unsigned int i;

	DBGPR("-->xgbe_free_ring_resources\n");

	for (i = 0; i < pdata->channel_count; i++) {
		channel = pdata->channel[i];
		xgbe_free_ring(pdata, channel->tx_ring);
		xgbe_free_ring(pdata, channel->rx_ring);
	}

	DBGPR("<--xgbe_free_ring_resources\n");
}