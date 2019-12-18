#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgbe_ring_desc {int dummy; } ;
struct TYPE_3__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct xgbe_ring_data {TYPE_1__ tx; struct xgbe_ring_desc* rdesc; } ;
struct TYPE_4__ {int queue_stopped; } ;
struct xgbe_ring {unsigned int cur; unsigned int dirty; TYPE_2__ tx; } ;
struct xgbe_desc_if {int /*<<< orphan*/  (* unmap_rdata ) (struct xgbe_prv_data*,struct xgbe_ring_data*) ;} ;
struct xgbe_hw_if {int /*<<< orphan*/  (* tx_desc_reset ) (struct xgbe_ring_data*) ;scalar_t__ (* is_last_desc ) (struct xgbe_ring_desc*) ;int /*<<< orphan*/  (* tx_complete ) (struct xgbe_ring_desc*) ;} ;
struct xgbe_prv_data {struct net_device* netdev; struct xgbe_desc_if desc_if; struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {int /*<<< orphan*/  queue_index; struct xgbe_ring* tx_ring; struct xgbe_prv_data* pdata; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*,...) ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,unsigned int) ; 
 int XGBE_TX_DESC_MAX_PROC ; 
 scalar_t__ XGBE_TX_DESC_MIN_FREE ; 
 int /*<<< orphan*/  dma_rmb () ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,unsigned int,unsigned int) ; 
 scalar_t__ netif_msg_tx_done (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  stub1 (struct xgbe_ring_desc*) ; 
 scalar_t__ stub2 (struct xgbe_ring_desc*) ; 
 int /*<<< orphan*/  stub3 (struct xgbe_prv_data*,struct xgbe_ring_data*) ; 
 int /*<<< orphan*/  stub4 (struct xgbe_ring_data*) ; 
 int /*<<< orphan*/  xgbe_dump_tx_desc (struct xgbe_prv_data*,struct xgbe_ring*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xgbe_tx_avail_desc (struct xgbe_ring*) ; 

__attribute__((used)) static int xgbe_tx_poll(struct xgbe_channel *channel)
{
	struct xgbe_prv_data *pdata = channel->pdata;
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_desc_if *desc_if = &pdata->desc_if;
	struct xgbe_ring *ring = channel->tx_ring;
	struct xgbe_ring_data *rdata;
	struct xgbe_ring_desc *rdesc;
	struct net_device *netdev = pdata->netdev;
	struct netdev_queue *txq;
	int processed = 0;
	unsigned int tx_packets = 0, tx_bytes = 0;
	unsigned int cur;

	DBGPR("-->xgbe_tx_poll\n");

	/* Nothing to do if there isn't a Tx ring for this channel */
	if (!ring)
		return 0;

	cur = ring->cur;

	/* Be sure we get ring->cur before accessing descriptor data */
	smp_rmb();

	txq = netdev_get_tx_queue(netdev, channel->queue_index);

	while ((processed < XGBE_TX_DESC_MAX_PROC) &&
	       (ring->dirty != cur)) {
		rdata = XGBE_GET_DESC_DATA(ring, ring->dirty);
		rdesc = rdata->rdesc;

		if (!hw_if->tx_complete(rdesc))
			break;

		/* Make sure descriptor fields are read after reading the OWN
		 * bit */
		dma_rmb();

		if (netif_msg_tx_done(pdata))
			xgbe_dump_tx_desc(pdata, ring, ring->dirty, 1, 0);

		if (hw_if->is_last_desc(rdesc)) {
			tx_packets += rdata->tx.packets;
			tx_bytes += rdata->tx.bytes;
		}

		/* Free the SKB and reset the descriptor for re-use */
		desc_if->unmap_rdata(pdata, rdata);
		hw_if->tx_desc_reset(rdata);

		processed++;
		ring->dirty++;
	}

	if (!processed)
		return 0;

	netdev_tx_completed_queue(txq, tx_packets, tx_bytes);

	if ((ring->tx.queue_stopped == 1) &&
	    (xgbe_tx_avail_desc(ring) > XGBE_TX_DESC_MIN_FREE)) {
		ring->tx.queue_stopped = 0;
		netif_tx_wake_queue(txq);
	}

	DBGPR("<--xgbe_tx_poll: processed=%d\n", processed);

	return processed;
}