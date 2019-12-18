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
struct ieee80211_device {size_t mgmt_queue_tail; size_t mgmt_queue_head; struct sk_buff** mgmt_queue_ring; } ;

/* Variables and functions */
 int MGMT_QUEUE_NUM ; 

__attribute__((used)) static struct sk_buff *dequeue_mgmt(struct ieee80211_device *ieee)
{
	struct sk_buff *ret;

	if (ieee->mgmt_queue_tail == ieee->mgmt_queue_head)
		return NULL;

	ret = ieee->mgmt_queue_ring[ieee->mgmt_queue_tail];

	ieee->mgmt_queue_tail =
		(ieee->mgmt_queue_tail + 1) % MGMT_QUEUE_NUM;

	return ret;
}