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
typedef  int u32 ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_4__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ stats; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {scalar_t__ ch_id; } ;
struct net_dev_context {struct net_device* dev; scalar_t__ is_mamac; TYPE_1__ rx; } ;
struct mbo {char* virt_address; int processed_length; scalar_t__ hdm_channel_id; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int EIO ; 
 int ETH_ALEN ; 
 scalar_t__ MDP_HDR_LEN ; 
 scalar_t__ MEP_HDR_LEN ; 
 scalar_t__ NET_RX_SUCCESS ; 
 int /*<<< orphan*/  PMS_IS_MEP (char*,int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_dev_context* get_net_dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  most_put_mbo (struct mbo*) ; 
 scalar_t__ netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pms_is_mamac (char*,int) ; 
 int /*<<< orphan*/  pr_err_once (char*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,...) ; 

__attribute__((used)) static int comp_rx_data(struct mbo *mbo)
{
	const u32 zero = 0;
	struct net_dev_context *nd;
	char *buf = mbo->virt_address;
	u32 len = mbo->processed_length;
	struct sk_buff *skb;
	struct net_device *dev;
	unsigned int skb_len;
	int ret = 0;

	nd = get_net_dev_hold(mbo->ifp);
	if (!nd)
		return -EIO;

	if (nd->rx.ch_id != mbo->hdm_channel_id) {
		ret = -EIO;
		goto put_nd;
	}

	dev = nd->dev;

	if (nd->is_mamac) {
		if (!pms_is_mamac(buf, len)) {
			ret = -EIO;
			goto put_nd;
		}

		skb = dev_alloc_skb(len - MDP_HDR_LEN + 2 * ETH_ALEN + 2);
	} else {
		if (!PMS_IS_MEP(buf, len)) {
			ret = -EIO;
			goto put_nd;
		}

		skb = dev_alloc_skb(len - MEP_HDR_LEN);
	}

	if (!skb) {
		dev->stats.rx_dropped++;
		pr_err_once("drop packet: no memory for skb\n");
		goto out;
	}

	skb->dev = dev;

	if (nd->is_mamac) {
		/* dest */
		ether_addr_copy(skb_put(skb, ETH_ALEN), dev->dev_addr);

		/* src */
		skb_put_data(skb, &zero, 4);
		skb_put_data(skb, buf + 5, 2);

		/* eth type */
		skb_put_data(skb, buf + 10, 2);

		buf += MDP_HDR_LEN;
		len -= MDP_HDR_LEN;
	} else {
		buf += MEP_HDR_LEN;
		len -= MEP_HDR_LEN;
	}

	skb_put_data(skb, buf, len);
	skb->protocol = eth_type_trans(skb, dev);
	skb_len = skb->len;
	if (netif_rx(skb) == NET_RX_SUCCESS) {
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb_len;
	} else {
		dev->stats.rx_dropped++;
	}

out:
	most_put_mbo(mbo);

put_nd:
	dev_put(nd->dev);
	return ret;
}