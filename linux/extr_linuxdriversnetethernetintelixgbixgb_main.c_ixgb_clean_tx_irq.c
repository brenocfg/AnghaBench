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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ixgb_tx_desc {int status; int popts; } ;
struct ixgb_desc_ring {unsigned int next_to_clean; unsigned int count; struct ixgb_buffer* buffer_info; int /*<<< orphan*/  next_to_use; } ;
struct ixgb_buffer {unsigned int next_to_watch; scalar_t__ time_stamp; } ;
struct ixgb_adapter {int detect_tx_hung; int /*<<< orphan*/  hw; struct net_device* netdev; int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/  hw_csum_tx_good; struct ixgb_desc_ring tx_ring; } ;

/* Variables and functions */
 scalar_t__ DESC_NEEDED ; 
 scalar_t__ HZ ; 
 scalar_t__ IXGB_DESC_UNUSED (struct ixgb_desc_ring*) ; 
 int IXGB_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IXGB_STATUS_TXOFF ; 
 struct ixgb_tx_desc* IXGB_TX_DESC (struct ixgb_desc_ring,unsigned int) ; 
 int IXGB_TX_DESC_POPTS_IXSM ; 
 int IXGB_TX_DESC_POPTS_TXSM ; 
 int IXGB_TX_DESC_STATUS_DD ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  __IXGB_DOWN ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ixgb_unmap_and_free_tx_resource (struct ixgb_adapter*,struct ixgb_buffer*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ixgb_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,int,int,int /*<<< orphan*/ ,unsigned int,scalar_t__,unsigned int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
ixgb_clean_tx_irq(struct ixgb_adapter *adapter)
{
	struct ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	struct net_device *netdev = adapter->netdev;
	struct ixgb_tx_desc *tx_desc, *eop_desc;
	struct ixgb_buffer *buffer_info;
	unsigned int i, eop;
	bool cleaned = false;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = IXGB_TX_DESC(*tx_ring, eop);

	while (eop_desc->status & IXGB_TX_DESC_STATUS_DD) {

		rmb(); /* read buffer_info after eop_desc */
		for (cleaned = false; !cleaned; ) {
			tx_desc = IXGB_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];

			if (tx_desc->popts &
			   (IXGB_TX_DESC_POPTS_TXSM |
			    IXGB_TX_DESC_POPTS_IXSM))
				adapter->hw_csum_tx_good++;

			ixgb_unmap_and_free_tx_resource(adapter, buffer_info);

			*(u32 *)&(tx_desc->status) = 0;

			cleaned = (i == eop);
			if (++i == tx_ring->count) i = 0;
		}

		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = IXGB_TX_DESC(*tx_ring, eop);
	}

	tx_ring->next_to_clean = i;

	if (unlikely(cleaned && netif_carrier_ok(netdev) &&
		     IXGB_DESC_UNUSED(tx_ring) >= DESC_NEEDED)) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean. */
		smp_mb();

		if (netif_queue_stopped(netdev) &&
		    !(test_bit(__IXGB_DOWN, &adapter->flags))) {
			netif_wake_queue(netdev);
			++adapter->restart_queue;
		}
	}

	if (adapter->detect_tx_hung) {
		/* detect a transmit hang in hardware, this serializes the
		 * check with the clearing of time_stamp and movement of i */
		adapter->detect_tx_hung = false;
		if (tx_ring->buffer_info[eop].time_stamp &&
		   time_after(jiffies, tx_ring->buffer_info[eop].time_stamp + HZ)
		   && !(IXGB_READ_REG(&adapter->hw, STATUS) &
		        IXGB_STATUS_TXOFF)) {
			/* detected Tx unit hang */
			netif_err(adapter, drv, adapter->netdev,
				  "Detected Tx Unit Hang\n"
				  "  TDH                  <%x>\n"
				  "  TDT                  <%x>\n"
				  "  next_to_use          <%x>\n"
				  "  next_to_clean        <%x>\n"
				  "buffer_info[next_to_clean]\n"
				  "  time_stamp           <%lx>\n"
				  "  next_to_watch        <%x>\n"
				  "  jiffies              <%lx>\n"
				  "  next_to_watch.status <%x>\n",
				  IXGB_READ_REG(&adapter->hw, TDH),
				  IXGB_READ_REG(&adapter->hw, TDT),
				  tx_ring->next_to_use,
				  tx_ring->next_to_clean,
				  tx_ring->buffer_info[eop].time_stamp,
				  eop,
				  jiffies,
				  eop_desc->status);
			netif_stop_queue(netdev);
		}
	}

	return cleaned;
}