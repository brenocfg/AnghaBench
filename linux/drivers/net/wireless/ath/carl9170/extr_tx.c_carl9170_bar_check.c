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
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_bar {int /*<<< orphan*/  frame_control; } ;
struct carl9170_bar_list_entry {int /*<<< orphan*/  list; struct sk_buff* skb; } ;
struct ar9170 {int /*<<< orphan*/ * bar_list_lock; int /*<<< orphan*/ * bar_list; } ;
struct _carl9170_tx_superframe {scalar_t__ frame_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 struct carl9170_bar_list_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carl9170_bar_check(struct ar9170 *ar, struct sk_buff *skb)
{
	struct _carl9170_tx_superframe *super = (void *) skb->data;
	struct ieee80211_bar *bar = (void *) super->frame_data;

	if (unlikely(ieee80211_is_back_req(bar->frame_control)) &&
	    skb->len >= sizeof(struct ieee80211_bar)) {
		struct carl9170_bar_list_entry *entry;
		unsigned int queue = skb_get_queue_mapping(skb);

		entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
		if (!WARN_ON_ONCE(!entry)) {
			entry->skb = skb;
			spin_lock_bh(&ar->bar_list_lock[queue]);
			list_add_tail_rcu(&entry->list, &ar->bar_list[queue]);
			spin_unlock_bh(&ar->bar_list_lock[queue]);
		}
	}
}