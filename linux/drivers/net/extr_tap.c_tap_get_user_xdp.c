#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdp_buff {struct tun_xdp_hdr* data; struct tun_xdp_hdr* data_end; struct tun_xdp_hdr* data_hard_start; } ;
struct virtio_net_hdr {int dummy; } ;
struct tun_xdp_hdr {int buflen; struct virtio_net_hdr gso; } ;
struct tap_queue {int flags; int /*<<< orphan*/  tap; int /*<<< orphan*/  vnet_hdr_sz; } ;
struct tap_dev {int /*<<< orphan*/  (* count_tx_dropped ) (struct tap_dev*) ;int /*<<< orphan*/  dev; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ h_proto; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int IFF_VNET_HDR ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ __vlan_get_protocol (struct sk_buff*,scalar_t__,int*) ; 
 struct sk_buff* build_skb (struct tun_xdp_hdr*,int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct tap_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_probe_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,struct tun_xdp_hdr*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,struct tun_xdp_hdr*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct tap_dev*) ; 
 int /*<<< orphan*/  tap_is_little_endian (struct tap_queue*) ; 
 int virtio_net_hdr_to_skb (struct sk_buff*,struct virtio_net_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tap_get_user_xdp(struct tap_queue *q, struct xdp_buff *xdp)
{
	struct tun_xdp_hdr *hdr = xdp->data_hard_start;
	struct virtio_net_hdr *gso = &hdr->gso;
	int buflen = hdr->buflen;
	int vnet_hdr_len = 0;
	struct tap_dev *tap;
	struct sk_buff *skb;
	int err, depth;

	if (q->flags & IFF_VNET_HDR)
		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);

	skb = build_skb(xdp->data_hard_start, buflen);
	if (!skb) {
		err = -ENOMEM;
		goto err;
	}

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	skb_put(skb, xdp->data_end - xdp->data);

	skb_set_network_header(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	if (vnet_hdr_len) {
		err = virtio_net_hdr_to_skb(skb, gso, tap_is_little_endian(q));
		if (err)
			goto err_kfree;
	}

	/* Move network header to the right position for VLAN tagged packets */
	if ((skb->protocol == htons(ETH_P_8021Q) ||
	     skb->protocol == htons(ETH_P_8021AD)) &&
	    __vlan_get_protocol(skb, skb->protocol, &depth) != 0)
		skb_set_network_header(skb, depth);

	rcu_read_lock();
	tap = rcu_dereference(q->tap);
	if (tap) {
		skb->dev = tap->dev;
		skb_probe_transport_header(skb);
		dev_queue_xmit(skb);
	} else {
		kfree_skb(skb);
	}
	rcu_read_unlock();

	return 0;

err_kfree:
	kfree_skb(skb);
err:
	rcu_read_lock();
	tap = rcu_dereference(q->tap);
	if (tap && tap->count_tx_dropped)
		tap->count_tx_dropped(tap);
	rcu_read_unlock();
	return err;
}