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
typedef  size_t u8 ;
struct wl1271_link {int /*<<< orphan*/ * tx_queue; } ;
struct wl1271 {struct wl1271_link* links; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 size_t WL12XX_INVALID_LINK_ID ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlcore_hw_lnk_high_prio (struct wl1271*,size_t,struct wl1271_link*) ; 
 scalar_t__ wlcore_hw_lnk_low_prio (struct wl1271*,size_t,struct wl1271_link*) ; 
 struct sk_buff* wlcore_lnk_dequeue (struct wl1271*,struct wl1271_link*,size_t) ; 

__attribute__((used)) static struct sk_buff *wlcore_lnk_dequeue_high_prio(struct wl1271 *wl,
						    u8 hlid, u8 ac,
						    u8 *low_prio_hlid)
{
	struct wl1271_link *lnk = &wl->links[hlid];

	if (!wlcore_hw_lnk_high_prio(wl, hlid, lnk)) {
		if (*low_prio_hlid == WL12XX_INVALID_LINK_ID &&
		    !skb_queue_empty(&lnk->tx_queue[ac]) &&
		    wlcore_hw_lnk_low_prio(wl, hlid, lnk))
			/* we found the first non-empty low priority queue */
			*low_prio_hlid = hlid;

		return NULL;
	}

	return wlcore_lnk_dequeue(wl, lnk, ac);
}