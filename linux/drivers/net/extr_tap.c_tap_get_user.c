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
typedef  int /*<<< orphan*/  vnet_hdr ;
struct virtio_net_hdr {int flags; scalar_t__ hdr_len; scalar_t__ csum_offset; scalar_t__ csum_start; int /*<<< orphan*/  member_0; } ;
struct ubuf_info {int /*<<< orphan*/  (* callback ) (struct ubuf_info*,int) ;} ;
struct tap_queue {int flags; int /*<<< orphan*/  tap; int /*<<< orphan*/  sk; int /*<<< orphan*/  vnet_hdr_sz; } ;
struct tap_dev {int /*<<< orphan*/  (* count_tx_dropped ) (struct tap_dev*) ;int /*<<< orphan*/  dev; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  dev; } ;
struct iov_iter {int dummy; } ;
typedef  unsigned long ssize_t ;
struct TYPE_4__ {scalar_t__ h_proto; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_flags; void* destructor_arg; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 unsigned long ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 unsigned long GOODCOPY_LEN ; 
 int IFF_VNET_HDR ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKBTX_DEV_ZEROCOPY ; 
 int /*<<< orphan*/  SKBTX_SHARED_FRAG ; 
 int SKB_MAX_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_ZEROCOPY ; 
 int /*<<< orphan*/  TAP_RESERVE ; 
 int VIRTIO_NET_HDR_F_NEEDS_CSUM ; 
 scalar_t__ __vlan_get_protocol (struct sk_buff*,scalar_t__,int*) ; 
 int /*<<< orphan*/  copy_from_iter_full (struct virtio_net_hdr*,int,struct iov_iter*) ; 
 scalar_t__ cpu_to_tap16 (struct tap_queue*,unsigned long) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,int) ; 
 unsigned long iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_npages (struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct tap_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int skb_copy_datagram_from_iter (struct sk_buff*,int /*<<< orphan*/ ,struct iov_iter*,unsigned long) ; 
 int /*<<< orphan*/  skb_probe_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ sock_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ubuf_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct tap_dev*) ; 
 unsigned long tap16_to_cpu (struct tap_queue*,scalar_t__) ; 
 struct sk_buff* tap_alloc_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t,int,int*) ; 
 int /*<<< orphan*/  tap_is_little_endian (struct tap_queue*) ; 
 scalar_t__ unlikely (int) ; 
 int virtio_net_hdr_to_skb (struct sk_buff*,struct virtio_net_hdr*,int /*<<< orphan*/ ) ; 
 int zerocopy_sg_from_iter (struct sk_buff*,struct iov_iter*) ; 

__attribute__((used)) static ssize_t tap_get_user(struct tap_queue *q, void *msg_control,
			    struct iov_iter *from, int noblock)
{
	int good_linear = SKB_MAX_HEAD(TAP_RESERVE);
	struct sk_buff *skb;
	struct tap_dev *tap;
	unsigned long total_len = iov_iter_count(from);
	unsigned long len = total_len;
	int err;
	struct virtio_net_hdr vnet_hdr = { 0 };
	int vnet_hdr_len = 0;
	int copylen = 0;
	int depth;
	bool zerocopy = false;
	size_t linear;

	if (q->flags & IFF_VNET_HDR) {
		vnet_hdr_len = READ_ONCE(q->vnet_hdr_sz);

		err = -EINVAL;
		if (len < vnet_hdr_len)
			goto err;
		len -= vnet_hdr_len;

		err = -EFAULT;
		if (!copy_from_iter_full(&vnet_hdr, sizeof(vnet_hdr), from))
			goto err;
		iov_iter_advance(from, vnet_hdr_len - sizeof(vnet_hdr));
		if ((vnet_hdr.flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
		     tap16_to_cpu(q, vnet_hdr.csum_start) +
		     tap16_to_cpu(q, vnet_hdr.csum_offset) + 2 >
			     tap16_to_cpu(q, vnet_hdr.hdr_len))
			vnet_hdr.hdr_len = cpu_to_tap16(q,
				 tap16_to_cpu(q, vnet_hdr.csum_start) +
				 tap16_to_cpu(q, vnet_hdr.csum_offset) + 2);
		err = -EINVAL;
		if (tap16_to_cpu(q, vnet_hdr.hdr_len) > len)
			goto err;
	}

	err = -EINVAL;
	if (unlikely(len < ETH_HLEN))
		goto err;

	if (msg_control && sock_flag(&q->sk, SOCK_ZEROCOPY)) {
		struct iov_iter i;

		copylen = vnet_hdr.hdr_len ?
			tap16_to_cpu(q, vnet_hdr.hdr_len) : GOODCOPY_LEN;
		if (copylen > good_linear)
			copylen = good_linear;
		else if (copylen < ETH_HLEN)
			copylen = ETH_HLEN;
		linear = copylen;
		i = *from;
		iov_iter_advance(&i, copylen);
		if (iov_iter_npages(&i, INT_MAX) <= MAX_SKB_FRAGS)
			zerocopy = true;
	}

	if (!zerocopy) {
		copylen = len;
		linear = tap16_to_cpu(q, vnet_hdr.hdr_len);
		if (linear > good_linear)
			linear = good_linear;
		else if (linear < ETH_HLEN)
			linear = ETH_HLEN;
	}

	skb = tap_alloc_skb(&q->sk, TAP_RESERVE, copylen,
			    linear, noblock, &err);
	if (!skb)
		goto err;

	if (zerocopy)
		err = zerocopy_sg_from_iter(skb, from);
	else
		err = skb_copy_datagram_from_iter(skb, 0, from, len);

	if (err)
		goto err_kfree;

	skb_set_network_header(skb, ETH_HLEN);
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;

	if (vnet_hdr_len) {
		err = virtio_net_hdr_to_skb(skb, &vnet_hdr,
					    tap_is_little_endian(q));
		if (err)
			goto err_kfree;
	}

	skb_probe_transport_header(skb);

	/* Move network header to the right position for VLAN tagged packets */
	if ((skb->protocol == htons(ETH_P_8021Q) ||
	     skb->protocol == htons(ETH_P_8021AD)) &&
	    __vlan_get_protocol(skb, skb->protocol, &depth) != 0)
		skb_set_network_header(skb, depth);

	rcu_read_lock();
	tap = rcu_dereference(q->tap);
	/* copy skb_ubuf_info for callback when skb has no error */
	if (zerocopy) {
		skb_shinfo(skb)->destructor_arg = msg_control;
		skb_shinfo(skb)->tx_flags |= SKBTX_DEV_ZEROCOPY;
		skb_shinfo(skb)->tx_flags |= SKBTX_SHARED_FRAG;
	} else if (msg_control) {
		struct ubuf_info *uarg = msg_control;
		uarg->callback(uarg, false);
	}

	if (tap) {
		skb->dev = tap->dev;
		dev_queue_xmit(skb);
	} else {
		kfree_skb(skb);
	}
	rcu_read_unlock();

	return total_len;

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