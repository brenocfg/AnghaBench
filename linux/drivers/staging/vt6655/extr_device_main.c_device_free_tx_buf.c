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
struct vnt_tx_desc {struct vnt_td_info* td_info; } ;
struct vnt_td_info {scalar_t__ flags; struct sk_buff* skb; } ;
struct vnt_private {int /*<<< orphan*/  hw; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void device_free_tx_buf(struct vnt_private *priv,
			       struct vnt_tx_desc *desc)
{
	struct vnt_td_info *td_info = desc->td_info;
	struct sk_buff *skb = td_info->skb;

	if (skb)
		ieee80211_tx_status_irqsafe(priv->hw, skb);

	td_info->skb = NULL;
	td_info->flags = 0;
}