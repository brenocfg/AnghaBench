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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct igbvf_ring {unsigned int next_to_use; TYPE_1__* buffer_info; } ;
struct igbvf_adapter {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ __be16 ;
struct TYPE_4__ {scalar_t__ nr_frags; } ;
struct TYPE_3__ {scalar_t__ time_stamp; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 unsigned int IGBVF_TX_FLAGS_CSUM ; 
 unsigned int IGBVF_TX_FLAGS_IPV4 ; 
 unsigned int IGBVF_TX_FLAGS_TSO ; 
 unsigned int IGBVF_TX_FLAGS_VLAN ; 
 unsigned int IGBVF_TX_FLAGS_VLAN_SHIFT ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ igbvf_maybe_stop_tx (struct net_device*,scalar_t__) ; 
 int igbvf_tso (struct igbvf_ring*,struct sk_buff*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ igbvf_tx_csum (struct igbvf_ring*,struct sk_buff*,unsigned int,scalar_t__) ; 
 int igbvf_tx_map_adv (struct igbvf_adapter*,struct igbvf_ring*,struct sk_buff*) ; 
 int /*<<< orphan*/  igbvf_tx_queue_adv (struct igbvf_adapter*,struct igbvf_ring*,unsigned int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t igbvf_xmit_frame_ring_adv(struct sk_buff *skb,
					     struct net_device *netdev,
					     struct igbvf_ring *tx_ring)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	unsigned int first, tx_flags = 0;
	u8 hdr_len = 0;
	int count = 0;
	int tso = 0;
	__be16 protocol = vlan_get_protocol(skb);

	if (test_bit(__IGBVF_DOWN, &adapter->state)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (skb->len <= 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	/* need: count + 4 desc gap to keep tail from touching
	 *       + 2 desc gap to keep tail from touching head,
	 *       + 1 desc for skb->data,
	 *       + 1 desc for context descriptor,
	 * head, otherwise try next time
	 */
	if (igbvf_maybe_stop_tx(netdev, skb_shinfo(skb)->nr_frags + 4)) {
		/* this is a hard error */
		return NETDEV_TX_BUSY;
	}

	if (skb_vlan_tag_present(skb)) {
		tx_flags |= IGBVF_TX_FLAGS_VLAN;
		tx_flags |= (skb_vlan_tag_get(skb) <<
			     IGBVF_TX_FLAGS_VLAN_SHIFT);
	}

	if (protocol == htons(ETH_P_IP))
		tx_flags |= IGBVF_TX_FLAGS_IPV4;

	first = tx_ring->next_to_use;

	tso = igbvf_tso(tx_ring, skb, tx_flags, &hdr_len);
	if (unlikely(tso < 0)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (tso)
		tx_flags |= IGBVF_TX_FLAGS_TSO;
	else if (igbvf_tx_csum(tx_ring, skb, tx_flags, protocol) &&
		 (skb->ip_summed == CHECKSUM_PARTIAL))
		tx_flags |= IGBVF_TX_FLAGS_CSUM;

	/* count reflects descriptors mapped, if 0 then mapping error
	 * has occurred and we need to rewind the descriptor queue
	 */
	count = igbvf_tx_map_adv(adapter, tx_ring, skb);

	if (count) {
		igbvf_tx_queue_adv(adapter, tx_ring, tx_flags, count,
				   first, skb->len, hdr_len);
		/* Make sure there is space in the ring for the next send. */
		igbvf_maybe_stop_tx(netdev, MAX_SKB_FRAGS + 4);
	} else {
		dev_kfree_skb_any(skb);
		tx_ring->buffer_info[first].time_stamp = 0;
		tx_ring->next_to_use = first;
	}

	return NETDEV_TX_OK;
}