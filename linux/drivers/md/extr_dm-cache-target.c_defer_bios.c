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
struct cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_bios; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (int /*<<< orphan*/ *,struct bio_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_deferred_bio_worker (struct cache*) ; 

__attribute__((used)) static void defer_bios(struct cache *cache, struct bio_list *bios)
{
	unsigned long flags;

	spin_lock_irqsave(&cache->lock, flags);
	bio_list_merge(&cache->deferred_bios, bios);
	bio_list_init(bios);
	spin_unlock_irqrestore(&cache->lock, flags);

	wake_deferred_bio_worker(cache);
}