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
struct net_device {int dummy; } ;
struct TYPE_4__ {int data; } ;
struct e1000_tx_desc {TYPE_2__ upper; } ;
struct e1000_ring {unsigned int next_to_clean; unsigned int count; unsigned int next_to_use; struct e1000_buffer* buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_hw {int dummy; } ;
struct e1000_buffer {unsigned int next_to_watch; scalar_t__ time_stamp; TYPE_1__* skb; scalar_t__ bytecount; scalar_t__ segs; } ;
struct e1000_adapter {int detect_tx_hung; int tx_timeout_factor; int tx_hang_recheck; unsigned int total_tx_bytes; unsigned int total_tx_packets; int /*<<< orphan*/  print_hang_task; int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  state; struct e1000_hw hw; struct net_device* netdev; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int E1000_STATUS_TXOFF ; 
 int /*<<< orphan*/  E1000_TXD_STAT_DD ; 
 struct e1000_tx_desc* E1000_TX_DESC (struct e1000_ring,unsigned int) ; 
 int HZ ; 
 int /*<<< orphan*/  STATUS ; 
 scalar_t__ TX_WAKE_THRESHOLD ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 scalar_t__ e1000_desc_unused (struct e1000_ring*) ; 
 int /*<<< orphan*/  e1000_put_txbuf (struct e1000_ring*,struct e1000_buffer*,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,unsigned int,unsigned int) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool e1000_clean_tx_irq(struct e1000_ring *tx_ring)
{
	struct e1000_adapter *adapter = tx_ring->adapter;
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_tx_desc *tx_desc, *eop_desc;
	struct e1000_buffer *buffer_info;
	unsigned int i, eop;
	unsigned int count = 0;
	unsigned int total_tx_bytes = 0, total_tx_packets = 0;
	unsigned int bytes_compl = 0, pkts_compl = 0;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = E1000_TX_DESC(*tx_ring, eop);

	while ((eop_desc->upper.data & cpu_to_le32(E1000_TXD_STAT_DD)) &&
	       (count < tx_ring->count)) {
		bool cleaned = false;

		dma_rmb();		/* read buffer_info after eop_desc */
		for (; !cleaned; count++) {
			tx_desc = E1000_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];
			cleaned = (i == eop);

			if (cleaned) {
				total_tx_packets += buffer_info->segs;
				total_tx_bytes += buffer_info->bytecount;
				if (buffer_info->skb) {
					bytes_compl += buffer_info->skb->len;
					pkts_compl++;
				}
			}

			e1000_put_txbuf(tx_ring, buffer_info, false);
			tx_desc->upper.data = 0;

			i++;
			if (i == tx_ring->count)
				i = 0;
		}

		if (i == tx_ring->next_to_use)
			break;
		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = E1000_TX_DESC(*tx_ring, eop);
	}

	tx_ring->next_to_clean = i;

	netdev_completed_queue(netdev, pkts_compl, bytes_compl);

#define TX_WAKE_THRESHOLD 32
	if (count && netif_carrier_ok(netdev) &&
	    e1000_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();

		if (netif_queue_stopped(netdev) &&
		    !(test_bit(__E1000_DOWN, &adapter->state))) {
			netif_wake_queue(netdev);
			++adapter->restart_queue;
		}
	}

	if (adapter->detect_tx_hung) {
		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of time_stamp and movement of i
		 */
		adapter->detect_tx_hung = false;
		if (tx_ring->buffer_info[i].time_stamp &&
		    time_after(jiffies, tx_ring->buffer_info[i].time_stamp
			       + (adapter->tx_timeout_factor * HZ)) &&
		    !(er32(STATUS) & E1000_STATUS_TXOFF))
			schedule_work(&adapter->print_hang_task);
		else
			adapter->tx_hang_recheck = false;
	}
	adapter->total_tx_bytes += total_tx_bytes;
	adapter->total_tx_packets += total_tx_packets;
	return count < tx_ring->count;
}