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
struct bio {int dummy; } ;
struct batcher {int commit_scheduled; int /*<<< orphan*/  lock; int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_commit (struct batcher*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void issue_after_commit(struct batcher *b, struct bio *bio)
{
       unsigned long flags;
       bool commit_scheduled;

       spin_lock_irqsave(&b->lock, flags);
       commit_scheduled = b->commit_scheduled;
       bio_list_add(&b->bios, bio);
       spin_unlock_irqrestore(&b->lock, flags);

       if (commit_scheduled)
	       async_commit(b);
}