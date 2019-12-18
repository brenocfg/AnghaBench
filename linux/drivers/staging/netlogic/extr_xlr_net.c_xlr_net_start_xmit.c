#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xlr_net_priv {int /*<<< orphan*/  tx_stnid; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct nlm_fmn_msg {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nlm_cop2_disable_irqrestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_cop2_enable_irqsave () ; 
 int nlm_fmn_send (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlm_fmn_msg*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_make_tx_desc (struct nlm_fmn_msg*,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t xlr_net_start_xmit(struct sk_buff *skb,
				      struct net_device *ndev)
{
	struct nlm_fmn_msg msg;
	struct xlr_net_priv *priv = netdev_priv(ndev);
	int ret;
	u32 flags;

	xlr_make_tx_desc(&msg, virt_to_phys(skb->data), skb);
	flags = nlm_cop2_enable_irqsave();
	ret = nlm_fmn_send(2, 0, priv->tx_stnid, &msg);
	nlm_cop2_disable_irqrestore(flags);
	if (ret)
		dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}