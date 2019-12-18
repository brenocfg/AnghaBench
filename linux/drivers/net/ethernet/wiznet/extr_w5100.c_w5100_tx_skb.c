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
typedef  scalar_t__ u16 ;
struct w5100_priv {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  S0_CR_SEND ; 
 int /*<<< orphan*/  W5100_S0_TX_WR (struct w5100_priv*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  w5100_command (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ w5100_read16 (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5100_write16 (struct w5100_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  w5100_writebuf (struct w5100_priv*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void w5100_tx_skb(struct net_device *ndev, struct sk_buff *skb)
{
	struct w5100_priv *priv = netdev_priv(ndev);
	u16 offset;

	offset = w5100_read16(priv, W5100_S0_TX_WR(priv));
	w5100_writebuf(priv, offset, skb->data, skb->len);
	w5100_write16(priv, W5100_S0_TX_WR(priv), offset + skb->len);
	ndev->stats.tx_bytes += skb->len;
	ndev->stats.tx_packets++;
	dev_kfree_skb(skb);

	w5100_command(priv, S0_CR_SEND);
}