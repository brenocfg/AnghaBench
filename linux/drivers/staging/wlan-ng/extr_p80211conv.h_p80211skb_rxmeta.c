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
struct p80211_rxmeta {int dummy; } ;
struct p80211_frmmeta {struct p80211_rxmeta* rx; } ;

/* Variables and functions */
 struct p80211_frmmeta* p80211skb_frmmeta (struct sk_buff*) ; 

__attribute__((used)) static inline struct p80211_rxmeta *p80211skb_rxmeta(struct sk_buff *skb)
{
	struct p80211_frmmeta *frmmeta = p80211skb_frmmeta(skb);

	return frmmeta ? frmmeta->rx : NULL;
}