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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct p54_sta_unlock {int /*<<< orphan*/  addr; } ;
struct p54_common {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  P54_CONTROL_TYPE_PSM_STA_UNLOCK ; 
 int /*<<< orphan*/  P54_HDR_FLAG_CONTROL_OPSET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff* p54_alloc_skb (struct p54_common*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54_tx (struct p54_common*,struct sk_buff*) ; 
 struct p54_sta_unlock* skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

int p54_sta_unlock(struct p54_common *priv, u8 *addr)
{
	struct sk_buff *skb;
	struct p54_sta_unlock *sta;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, sizeof(*sta),
			    P54_CONTROL_TYPE_PSM_STA_UNLOCK, GFP_ATOMIC);
	if (unlikely(!skb))
		return -ENOMEM;

	sta = skb_put(skb, sizeof(*sta));
	memcpy(sta->addr, addr, ETH_ALEN);
	p54_tx(priv, skb);
	return 0;
}