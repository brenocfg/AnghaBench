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
struct sk_buff {int dummy; } ;
struct ath6kl {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_TM_ATTR_CMD ; 
 int /*<<< orphan*/  ATH6KL_TM_ATTR_DATA ; 
 int /*<<< orphan*/  ATH6KL_TM_CMD_TCMD ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 struct sk_buff* cfg80211_testmode_alloc_event_skb (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_testmode_event (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,size_t,void*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath6kl_tm_rx_event(struct ath6kl *ar, void *buf, size_t buf_len)
{
	struct sk_buff *skb;

	if (!buf || buf_len == 0)
		return;

	skb = cfg80211_testmode_alloc_event_skb(ar->wiphy, buf_len, GFP_KERNEL);
	if (!skb) {
		ath6kl_warn("failed to allocate testmode rx skb!\n");
		return;
	}
	if (nla_put_u32(skb, ATH6KL_TM_ATTR_CMD, ATH6KL_TM_CMD_TCMD) ||
	    nla_put(skb, ATH6KL_TM_ATTR_DATA, buf_len, buf))
		goto nla_put_failure;
	cfg80211_testmode_event(skb, GFP_KERNEL);
	return;

nla_put_failure:
	kfree_skb(skb);
	ath6kl_warn("nla_put failed on testmode rx skb!\n");
}