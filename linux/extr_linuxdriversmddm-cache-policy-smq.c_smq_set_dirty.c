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
struct smq_policy {int /*<<< orphan*/  lock; } ;
struct dm_cache_policy {int dummy; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  __smq_set_clear_dirty (struct smq_policy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct smq_policy* to_smq_policy (struct dm_cache_policy*) ; 

__attribute__((used)) static void smq_set_dirty(struct dm_cache_policy *p, dm_cblock_t cblock)
{
	unsigned long flags;
	struct smq_policy *mq = to_smq_policy(p);

	spin_lock_irqsave(&mq->lock, flags);
	__smq_set_clear_dirty(mq, cblock, true);
	spin_unlock_irqrestore(&mq->lock, flags);
}