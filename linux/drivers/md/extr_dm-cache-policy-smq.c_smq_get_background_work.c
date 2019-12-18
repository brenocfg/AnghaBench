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
struct smq_policy {int /*<<< orphan*/  lock; int /*<<< orphan*/  bg_work; } ;
struct policy_work {int dummy; } ;
struct dm_cache_policy {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int btracker_issue (int /*<<< orphan*/ ,struct policy_work**) ; 
 int /*<<< orphan*/  clean_target_met (struct smq_policy*,int) ; 
 int /*<<< orphan*/  queue_writeback (struct smq_policy*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct smq_policy* to_smq_policy (struct dm_cache_policy*) ; 

__attribute__((used)) static int smq_get_background_work(struct dm_cache_policy *p, bool idle,
				   struct policy_work **result)
{
	int r;
	unsigned long flags;
	struct smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	r = btracker_issue(mq->bg_work, result);
	if (r == -ENODATA) {
		if (!clean_target_met(mq, idle)) {
			queue_writeback(mq, idle);
			r = btracker_issue(mq->bg_work, result);
		}
	}
	spin_unlock_irqrestore(&mq->lock, flags);

	return r;
}