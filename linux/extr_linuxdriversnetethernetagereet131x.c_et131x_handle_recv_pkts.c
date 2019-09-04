#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rx_ring {scalar_t__ num_ready_recv; int unfinished_receives; int /*<<< orphan*/  recv_list; } ;
struct rfd {scalar_t__ len; } ;
struct et131x_adapter {TYPE_4__* regs; TYPE_2__* pdev; TYPE_5__* netdev; int /*<<< orphan*/  packet_filter; struct rx_ring rx_ring; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_packets; } ;
struct TYPE_10__ {TYPE_1__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  watchdog_timer; } ;
struct TYPE_9__ {TYPE_3__ global; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_PACKETS_HANDLED ; 
 int NANO_IN_A_MICRO ; 
 int PARM_TX_TIME_INT_DEF ; 
 scalar_t__ RFD_LOW_WATER_MARK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (TYPE_5__*) ; 
 struct rfd* nic_rx_pkts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int et131x_handle_recv_pkts(struct et131x_adapter *adapter, int budget)
{
	struct rfd *rfd = NULL;
	int count = 0;
	int limit = budget;
	bool done = true;
	struct rx_ring *rx_ring = &adapter->rx_ring;

	if (budget > MAX_PACKETS_HANDLED)
		limit = MAX_PACKETS_HANDLED;

	/* Process up to available RFD's */
	while (count < limit) {
		if (list_empty(&rx_ring->recv_list)) {
			WARN_ON(rx_ring->num_ready_recv != 0);
			done = false;
			break;
		}

		rfd = nic_rx_pkts(adapter);

		if (rfd == NULL)
			break;

		/* Do not receive any packets until a filter has been set.
		 * Do not receive any packets until we have link.
		 * If length is zero, return the RFD in order to advance the
		 * Free buffer ring.
		 */
		if (!adapter->packet_filter ||
		    !netif_carrier_ok(adapter->netdev) ||
		    rfd->len == 0)
			continue;

		adapter->netdev->stats.rx_packets++;

		if (rx_ring->num_ready_recv < RFD_LOW_WATER_MARK)
			dev_warn(&adapter->pdev->dev, "RFD's are running out\n");

		count++;
	}

	if (count == limit || !done) {
		rx_ring->unfinished_receives = true;
		writel(PARM_TX_TIME_INT_DEF * NANO_IN_A_MICRO,
		       &adapter->regs->global.watchdog_timer);
	} else {
		/* Watchdog timer will disable itself if appropriate. */
		rx_ring->unfinished_receives = false;
	}

	return count;
}