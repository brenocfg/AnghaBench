#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct chtls_dev {TYPE_1__ deferq; int /*<<< orphan*/  deferq_task; } ;
typedef  int /*<<< orphan*/  defer_handler_t ;
struct TYPE_5__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 TYPE_3__* DEFERRED_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int skb_queue_len (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void t4_defer_reply(struct sk_buff *skb, struct chtls_dev *cdev,
			   defer_handler_t handler)
{
	DEFERRED_SKB_CB(skb)->handler = handler;
	spin_lock_bh(&cdev->deferq.lock);
	__skb_queue_tail(&cdev->deferq, skb);
	if (skb_queue_len(&cdev->deferq) == 1)
		schedule_work(&cdev->deferq_task);
	spin_unlock_bh(&cdev->deferq.lock);
}