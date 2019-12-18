#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct kvaser_pciefd_rx_packet {int* header; int timestamp; } ;
struct TYPE_8__ {int txerr; int rxerr; } ;
struct TYPE_5__ {int /*<<< orphan*/  restarts; } ;
struct TYPE_6__ {int state; TYPE_1__ can_stats; scalar_t__ restart_ms; struct net_device* dev; } ;
struct kvaser_pciefd_can {int /*<<< orphan*/  bec_poll_timer; TYPE_4__ bec; TYPE_3__* kv_pcie; TYPE_2__ can; } ;
struct can_frame {int* data; int /*<<< orphan*/  can_id; } ;
struct can_berr_counter {int txerr; int rxerr; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;
struct TYPE_7__ {int /*<<< orphan*/  freq_to_ticks_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_RESTARTED ; 
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KVASER_PCIEFD_BEC_POLL_FREQ ; 
 int KVASER_PCIEFD_SPACK_RXERR_SHIFT ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  div_u64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_pciefd_change_state (struct kvaser_pciefd_can*,struct can_frame*,int,int,int) ; 
 int /*<<< orphan*/  kvaser_pciefd_packet_to_state (struct kvaser_pciefd_rx_packet*,struct can_berr_counter*,int*,int*,int*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 

__attribute__((used)) static int kvaser_pciefd_handle_status_resp(struct kvaser_pciefd_can *can,
					    struct kvaser_pciefd_rx_packet *p)
{
	struct can_berr_counter bec;
	enum can_state old_state, new_state, tx_state, rx_state;

	old_state = can->can.state;

	bec.txerr = p->header[0] & 0xff;
	bec.rxerr = (p->header[0] >> KVASER_PCIEFD_SPACK_RXERR_SHIFT) & 0xff;

	kvaser_pciefd_packet_to_state(p, &bec, &new_state, &tx_state,
				      &rx_state);

	if (new_state != old_state) {
		struct net_device *ndev = can->can.dev;
		struct sk_buff *skb;
		struct can_frame *cf;
		struct skb_shared_hwtstamps *shhwtstamps;

		skb = alloc_can_err_skb(ndev, &cf);
		if (!skb) {
			struct net_device_stats *stats = &ndev->stats;

			stats->rx_dropped++;
			return -ENOMEM;
		}

		kvaser_pciefd_change_state(can, cf, new_state, tx_state,
					   rx_state);

		if (old_state == CAN_STATE_BUS_OFF &&
		    new_state == CAN_STATE_ERROR_ACTIVE &&
		    can->can.restart_ms) {
			can->can.can_stats.restarts++;
			cf->can_id |= CAN_ERR_RESTARTED;
		}

		shhwtstamps = skb_hwtstamps(skb);
		shhwtstamps->hwtstamp =
			ns_to_ktime(div_u64(p->timestamp * 1000,
					    can->kv_pcie->freq_to_ticks_div));

		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;

		netif_rx(skb);
	}
	can->bec.txerr = bec.txerr;
	can->bec.rxerr = bec.rxerr;
	/* Check if we need to poll the error counters */
	if (bec.txerr || bec.rxerr)
		mod_timer(&can->bec_poll_timer, KVASER_PCIEFD_BEC_POLL_FREQ);

	return 0;
}