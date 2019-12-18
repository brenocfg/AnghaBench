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
typedef  scalar_t__ u32 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  general_rx; } ;
struct TYPE_3__ {scalar_t__ minor_max; scalar_t__ sync_event_diff_max; scalar_t__ sync_event_diff_min; } ;
struct efx_ptp_data {TYPE_2__ ts_corrections; int /*<<< orphan*/  (* nic_to_kernel_time ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;TYPE_1__ nic_time; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_ptp_data* ptp_data; } ;
struct efx_channel {scalar_t__ sync_events_state; scalar_t__ sync_timestamp_minor; int /*<<< orphan*/  sync_timestamp_major; struct efx_nic* efx; } ;

/* Variables and functions */
 scalar_t__ SYNC_EVENTS_VALID ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ efx_rx_buf_timestamp_minor (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_vdbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void __efx_rx_skb_attach_timestamp(struct efx_channel *channel,
				   struct sk_buff *skb)
{
	struct efx_nic *efx = channel->efx;
	struct efx_ptp_data *ptp = efx->ptp_data;
	u32 pkt_timestamp_major, pkt_timestamp_minor;
	u32 diff, carry;
	struct skb_shared_hwtstamps *timestamps;

	if (channel->sync_events_state != SYNC_EVENTS_VALID)
		return;

	pkt_timestamp_minor = efx_rx_buf_timestamp_minor(efx, skb_mac_header(skb));

	/* get the difference between the packet and sync timestamps,
	 * modulo one second
	 */
	diff = pkt_timestamp_minor - channel->sync_timestamp_minor;
	if (pkt_timestamp_minor < channel->sync_timestamp_minor)
		diff += ptp->nic_time.minor_max;

	/* do we roll over a second boundary and need to carry the one? */
	carry = (channel->sync_timestamp_minor >= ptp->nic_time.minor_max - diff) ?
		1 : 0;

	if (diff <= ptp->nic_time.sync_event_diff_max) {
		/* packet is ahead of the sync event by a quarter of a second or
		 * less (allowing for fuzz)
		 */
		pkt_timestamp_major = channel->sync_timestamp_major + carry;
	} else if (diff >= ptp->nic_time.sync_event_diff_min) {
		/* packet is behind the sync event but within the fuzz factor.
		 * This means the RX packet and sync event crossed as they were
		 * placed on the event queue, which can sometimes happen.
		 */
		pkt_timestamp_major = channel->sync_timestamp_major - 1 + carry;
	} else {
		/* it's outside tolerance in both directions. this might be
		 * indicative of us missing sync events for some reason, so
		 * we'll call it an error rather than risk giving a bogus
		 * timestamp.
		 */
		netif_vdbg(efx, drv, efx->net_dev,
			  "packet timestamp %x too far from sync event %x:%x\n",
			  pkt_timestamp_minor, channel->sync_timestamp_major,
			  channel->sync_timestamp_minor);
		return;
	}

	/* attach the timestamps to the skb */
	timestamps = skb_hwtstamps(skb);
	timestamps->hwtstamp =
		ptp->nic_to_kernel_time(pkt_timestamp_major,
					pkt_timestamp_minor,
					ptp->ts_corrections.general_rx);
}