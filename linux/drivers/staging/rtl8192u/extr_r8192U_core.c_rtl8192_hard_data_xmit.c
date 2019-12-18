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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ cb; } ;
struct r8192_priv {int /*<<< orphan*/  tx_lock; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct cb_desc {scalar_t__ queue_index; int bTxEnableFwCalcDur; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_headroom; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  RTL8192U_ASSERT (int) ; 
 scalar_t__ TXCMD_QUEUE ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int rtl8192_tx (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtl8192_hard_data_xmit(struct sk_buff *skb, struct net_device *dev,
				   int rate)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	int ret;
	unsigned long flags;
	struct cb_desc *tcb_desc = (struct cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	/* shall not be referred by command packet */
	RTL8192U_ASSERT(queue_index != TXCMD_QUEUE);

	spin_lock_irqsave(&priv->tx_lock, flags);

	*(struct net_device **)(skb->cb) = dev;
	tcb_desc->bTxEnableFwCalcDur = 1;
	skb_push(skb, priv->ieee80211->tx_headroom);
	ret = rtl8192_tx(dev, skb);

	spin_unlock_irqrestore(&priv->tx_lock, flags);
}