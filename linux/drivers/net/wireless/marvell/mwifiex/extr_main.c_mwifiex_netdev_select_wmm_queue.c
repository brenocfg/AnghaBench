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

/* Variables and functions */
 size_t cfg80211_classify8021d (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mwifiex_1d_to_wmm_queue ; 

__attribute__((used)) static u16
mwifiex_netdev_select_wmm_queue(struct net_device *dev, struct sk_buff *skb,
				struct net_device *sb_dev)
{
	skb->priority = cfg80211_classify8021d(skb, NULL);
	return mwifiex_1d_to_wmm_queue[skb->priority];
}