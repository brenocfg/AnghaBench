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
struct zfcp_reqlist {int /*<<< orphan*/  lock; int /*<<< orphan*/ * buckets; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 unsigned int ZFCP_REQ_LIST_BUCKETS ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void zfcp_reqlist_move(struct zfcp_reqlist *rl,
				     struct list_head *list)
{
	unsigned int i;
	unsigned long flags;

	spin_lock_irqsave(&rl->lock, flags);
	for (i = 0; i < ZFCP_REQ_LIST_BUCKETS; i++)
		list_splice_init(&rl->buckets[i], list);
	spin_unlock_irqrestore(&rl->lock, flags);
}