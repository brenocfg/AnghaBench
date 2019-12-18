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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {size_t priority; } ;
struct net_device {int dummy; } ;
struct mlme_priv {scalar_t__ acm_mask; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 size_t qos_acm (scalar_t__,size_t) ; 
 int /*<<< orphan*/ * rtw_1d_to_queue ; 
 size_t rtw_classify8021d (struct sk_buff*) ; 
 struct adapter* rtw_netdev_priv (struct net_device*) ; 

__attribute__((used)) static u16 rtw_select_queue(struct net_device *dev, struct sk_buff *skb,
			    struct net_device *sb_dev)
{
	struct adapter	*padapter = rtw_netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	skb->priority = rtw_classify8021d(skb);

	if (pmlmepriv->acm_mask != 0)
		skb->priority = qos_acm(pmlmepriv->acm_mask, skb->priority);

	return rtw_1d_to_queue[skb->priority];
}