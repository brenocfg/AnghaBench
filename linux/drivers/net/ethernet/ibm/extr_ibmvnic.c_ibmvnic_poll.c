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
struct TYPE_4__ {int flags; scalar_t__ first; int /*<<< orphan*/  vlan_tci; scalar_t__ off_frame_data; int /*<<< orphan*/  len; scalar_t__ rc; int /*<<< orphan*/  correlator; } ;
union sub_crq {TYPE_1__ rx_comp; } ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct napi_struct {struct net_device* dev; } ;
struct ibmvnic_rx_buff {scalar_t__ data; struct sk_buff* skb; } ;
struct ibmvnic_adapter {int napi; scalar_t__ reset_reason; scalar_t__ state; int /*<<< orphan*/ * rx_scrq; int /*<<< orphan*/ * rx_pool; TYPE_3__* rx_stats_buffers; scalar_t__ rx_vlan_header_insertion; int /*<<< orphan*/  resetting; } ;
struct TYPE_6__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int IBMVNIC_IP_CHKSUM_GOOD ; 
 int IBMVNIC_TCP_UDP_CHKSUM_GOOD ; 
 int IBMVNIC_VLAN_STRIPPED ; 
 scalar_t__ VNIC_CLOSING ; 
 scalar_t__ VNIC_RESET_NON_FATAL ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  disable_scrq_irq (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_scrq_irq (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 union sub_crq* ibmvnic_next_scrq (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 scalar_t__ napi_reschedule (struct napi_struct*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ pending_scrq (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_buff_from_pool (struct ibmvnic_adapter*,struct ibmvnic_rx_buff*) ; 
 int /*<<< orphan*/  replenish_rx_pool (struct ibmvnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ibmvnic_poll(struct napi_struct *napi, int budget)
{
	struct net_device *netdev = napi->dev;
	struct ibmvnic_adapter *adapter = netdev_priv(netdev);
	int scrq_num = (int)(napi - adapter->napi);
	int frames_processed = 0;

restart_poll:
	while (frames_processed < budget) {
		struct sk_buff *skb;
		struct ibmvnic_rx_buff *rx_buff;
		union sub_crq *next;
		u32 length;
		u16 offset;
		u8 flags = 0;

		if (unlikely(test_bit(0, &adapter->resetting) &&
			     adapter->reset_reason != VNIC_RESET_NON_FATAL)) {
			enable_scrq_irq(adapter, adapter->rx_scrq[scrq_num]);
			napi_complete_done(napi, frames_processed);
			return frames_processed;
		}

		if (!pending_scrq(adapter, adapter->rx_scrq[scrq_num]))
			break;
		next = ibmvnic_next_scrq(adapter, adapter->rx_scrq[scrq_num]);
		rx_buff =
		    (struct ibmvnic_rx_buff *)be64_to_cpu(next->
							  rx_comp.correlator);
		/* do error checking */
		if (next->rx_comp.rc) {
			netdev_dbg(netdev, "rx buffer returned with rc %x\n",
				   be16_to_cpu(next->rx_comp.rc));
			/* free the entry */
			next->rx_comp.first = 0;
			dev_kfree_skb_any(rx_buff->skb);
			remove_buff_from_pool(adapter, rx_buff);
			continue;
		} else if (!rx_buff->skb) {
			/* free the entry */
			next->rx_comp.first = 0;
			remove_buff_from_pool(adapter, rx_buff);
			continue;
		}

		length = be32_to_cpu(next->rx_comp.len);
		offset = be16_to_cpu(next->rx_comp.off_frame_data);
		flags = next->rx_comp.flags;
		skb = rx_buff->skb;
		skb_copy_to_linear_data(skb, rx_buff->data + offset,
					length);

		/* VLAN Header has been stripped by the system firmware and
		 * needs to be inserted by the driver
		 */
		if (adapter->rx_vlan_header_insertion &&
		    (flags & IBMVNIC_VLAN_STRIPPED))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       ntohs(next->rx_comp.vlan_tci));

		/* free the entry */
		next->rx_comp.first = 0;
		remove_buff_from_pool(adapter, rx_buff);

		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, scrq_num);

		if (flags & IBMVNIC_IP_CHKSUM_GOOD &&
		    flags & IBMVNIC_TCP_UDP_CHKSUM_GOOD) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		}

		length = skb->len;
		napi_gro_receive(napi, skb); /* send it up */
		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += length;
		adapter->rx_stats_buffers[scrq_num].packets++;
		adapter->rx_stats_buffers[scrq_num].bytes += length;
		frames_processed++;
	}

	if (adapter->state != VNIC_CLOSING)
		replenish_rx_pool(adapter, &adapter->rx_pool[scrq_num]);

	if (frames_processed < budget) {
		enable_scrq_irq(adapter, adapter->rx_scrq[scrq_num]);
		napi_complete_done(napi, frames_processed);
		if (pending_scrq(adapter, adapter->rx_scrq[scrq_num]) &&
		    napi_reschedule(napi)) {
			disable_scrq_irq(adapter, adapter->rx_scrq[scrq_num]);
			goto restart_poll;
		}
	}
	return frames_processed;
}