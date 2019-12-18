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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct device {int dummy; } ;
struct net_device {TYPE_1__ stats; struct device dev; } ;
struct emac_priv {int /*<<< orphan*/  rxchan; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cpdma_chan_submit (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* emac_rx_alloc (struct emac_priv*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ net_ratelimit () ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_rx_err (struct emac_priv*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void emac_rx_handler(void *token, int len, int status)
{
	struct sk_buff		*skb = token;
	struct net_device	*ndev = skb->dev;
	struct emac_priv	*priv = netdev_priv(ndev);
	struct device		*emac_dev = &ndev->dev;
	int			ret;

	/* free and bail if we are shutting down */
	if (unlikely(!netif_running(ndev))) {
		dev_kfree_skb_any(skb);
		return;
	}

	/* recycle on receive error */
	if (status < 0) {
		ndev->stats.rx_errors++;
		goto recycle;
	}

	/* feed received packet up the stack */
	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, ndev);
	netif_receive_skb(skb);
	ndev->stats.rx_bytes += len;
	ndev->stats.rx_packets++;

	/* alloc a new packet for receive */
	skb = emac_rx_alloc(priv);
	if (!skb) {
		if (netif_msg_rx_err(priv) && net_ratelimit())
			dev_err(emac_dev, "failed rx buffer alloc\n");
		return;
	}

recycle:
	ret = cpdma_chan_submit(priv->rxchan, skb, skb->data,
			skb_tailroom(skb), 0);

	WARN_ON(ret == -ENOMEM);
	if (unlikely(ret < 0))
		dev_kfree_skb_any(skb);
}