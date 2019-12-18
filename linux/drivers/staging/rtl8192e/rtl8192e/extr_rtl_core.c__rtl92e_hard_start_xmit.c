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
struct r8192_priv {TYPE_1__* rtllib; scalar_t__ bResetInProgress; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct cb_desc {scalar_t__ queue_index; int RATRIndex; int bTxDisableRateFallBack; int bTxUseDriverAssingedRate; int bTxEnableFwCalcDur; } ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_2__ {scalar_t__ eRFPowerState; int /*<<< orphan*/  tx_headroom; } ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 scalar_t__ TXCMD_QUEUE ; 
 int _rtl92e_tx (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  _rtl92e_tx_cmd (struct net_device*,struct sk_buff*) ; 
 scalar_t__ eRfOff ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct net_device**,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _rtl92e_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int ret;
	struct cb_desc *tcb_desc = (struct cb_desc *)(skb->cb +
				    MAX_DEV_ADDR_SIZE);
	u8 queue_index = tcb_desc->queue_index;

	if (queue_index != TXCMD_QUEUE) {
		if ((priv->rtllib->eRFPowerState == eRfOff) ||
		     !priv->up || priv->bResetInProgress) {
			kfree_skb(skb);
			return 0;
		}
	}

	memcpy((unsigned char *)(skb->cb), &dev, sizeof(dev));
	if (queue_index == TXCMD_QUEUE) {
		_rtl92e_tx_cmd(dev, skb);
		return 0;
	}

	tcb_desc->RATRIndex = 7;
	tcb_desc->bTxDisableRateFallBack = 1;
	tcb_desc->bTxUseDriverAssingedRate = 1;
	tcb_desc->bTxEnableFwCalcDur = 1;
	skb_push(skb, priv->rtllib->tx_headroom);
	ret = _rtl92e_tx(dev, skb);
	if (ret != 0)
		kfree_skb(skb);
	return ret;
}