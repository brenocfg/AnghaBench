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
struct smq_policy {int /*<<< orphan*/  lock; int /*<<< orphan*/  tick; } ;
struct dm_cache_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_cache_period (struct smq_policy*) ; 
 int /*<<< orphan*/  end_hotspot_period (struct smq_policy*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct smq_policy* to_smq_policy (struct dm_cache_policy*) ; 
 int /*<<< orphan*/  update_sentinels (struct smq_policy*) ; 

__attribute__((used)) static void smq_tick(struct dm_cache_policy *p, bool can_block)
{
	struct smq_policy *mq = to_smq_policy(p);
	unsigned long flags;

	spin_lock_irqsave(&mq->lock, flags);
	mq->tick++;
	update_sentinels(mq);
	end_hotspot_period(mq);
	end_cache_period(mq);
	spin_unlock_irqrestore(&mq->lock, flags);
}