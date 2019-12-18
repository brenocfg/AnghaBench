#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct iavf_vsi {TYPE_1__* back; struct net_device* netdev; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {int prev_pkt_ctr; } ;
struct TYPE_5__ {int packets; } ;
struct iavf_ring {TYPE_3__ tx_stats; int /*<<< orphan*/  q_vector; TYPE_2__ stats; scalar_t__ desc; } ;
struct TYPE_4__ {unsigned int num_active_queues; struct iavf_ring* tx_rings; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  __IAVF_VSI_DOWN ; 
 int /*<<< orphan*/  iavf_force_wb (struct iavf_vsi*,int /*<<< orphan*/ ) ; 
 scalar_t__ iavf_get_tx_pending (struct iavf_ring*,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iavf_detect_recover_hung(struct iavf_vsi *vsi)
{
	struct iavf_ring *tx_ring = NULL;
	struct net_device *netdev;
	unsigned int i;
	int packets;

	if (!vsi)
		return;

	if (test_bit(__IAVF_VSI_DOWN, vsi->state))
		return;

	netdev = vsi->netdev;
	if (!netdev)
		return;

	if (!netif_carrier_ok(netdev))
		return;

	for (i = 0; i < vsi->back->num_active_queues; i++) {
		tx_ring = &vsi->back->tx_rings[i];
		if (tx_ring && tx_ring->desc) {
			/* If packet counter has not changed the queue is
			 * likely stalled, so force an interrupt for this
			 * queue.
			 *
			 * prev_pkt_ctr would be negative if there was no
			 * pending work.
			 */
			packets = tx_ring->stats.packets & INT_MAX;
			if (tx_ring->tx_stats.prev_pkt_ctr == packets) {
				iavf_force_wb(vsi, tx_ring->q_vector);
				continue;
			}

			/* Memory barrier between read of packet count and call
			 * to iavf_get_tx_pending()
			 */
			smp_rmb();
			tx_ring->tx_stats.prev_pkt_ctr =
			  iavf_get_tx_pending(tx_ring, true) ? packets : -1;
		}
	}
}