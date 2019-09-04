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
struct t3cdev {int dummy; } ;
struct sk_buff {int cb; } ;
struct iwch_ep_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_ep (struct iwch_ep_common*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxq ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_work ; 
 int /*<<< orphan*/  workq ; 

__attribute__((used)) static int sched(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct iwch_ep_common *epc = ctx;

	get_ep(epc);

	/*
	 * Save ctx and tdev in the skb->cb area.
	 */
	*((void **) skb->cb) = ctx;
	*((struct t3cdev **) (skb->cb + sizeof(void *))) = tdev;

	/*
	 * Queue the skb and schedule the worker thread.
	 */
	skb_queue_tail(&rxq, skb);
	queue_work(workq, &skb_work);
	return 0;
}