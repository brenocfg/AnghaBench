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
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  len; } ;
struct tx_desc {TYPE_1__ header; int /*<<< orphan*/  data; } ;
struct sk_buff {unsigned int len; } ;
struct net_device {int dummy; } ;
struct ec_bhf_priv {size_t tx_dnext; int tx_dcount; unsigned int stat_tx_bytes; struct tx_desc* tx_descs; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  TX_HDR_PORT_0 ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ec_bhf_desc_sent (struct tx_desc*) ; 
 int /*<<< orphan*/  ec_bhf_send_packet (struct ec_bhf_priv*,struct tx_desc*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct ec_bhf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_and_csum_dev (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static netdev_tx_t ec_bhf_start_xmit(struct sk_buff *skb,
				     struct net_device *net_dev)
{
	struct ec_bhf_priv *priv = netdev_priv(net_dev);
	struct tx_desc *desc;
	unsigned len;

	desc = &priv->tx_descs[priv->tx_dnext];

	skb_copy_and_csum_dev(skb, desc->data);
	len = skb->len;

	memset(&desc->header, 0, sizeof(desc->header));
	desc->header.len = cpu_to_le16(len);
	desc->header.port = TX_HDR_PORT_0;

	ec_bhf_send_packet(priv, desc);

	priv->tx_dnext = (priv->tx_dnext + 1) % priv->tx_dcount;

	if (!ec_bhf_desc_sent(&priv->tx_descs[priv->tx_dnext])) {
		/* Make sure that updates to tx_dnext are perceived
		 * by timer routine.
		 */
		smp_wmb();

		netif_stop_queue(net_dev);
	}

	priv->stat_tx_bytes += len;

	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}