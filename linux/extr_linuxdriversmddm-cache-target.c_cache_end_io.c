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
struct per_bio_data {scalar_t__ tick; } ;
struct dm_target {struct cache* private; } ;
struct cache {int need_tick_bio; int /*<<< orphan*/  lock; int /*<<< orphan*/  policy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int DM_ENDIO_DONE ; 
 int /*<<< orphan*/  accounted_complete (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  bio_drop_shared_lock (struct cache*,struct bio*) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  policy_tick (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cache_end_io(struct dm_target *ti, struct bio *bio, blk_status_t *error)
{
	struct cache *cache = ti->private;
	unsigned long flags;
	struct per_bio_data *pb = get_per_bio_data(bio);

	if (pb->tick) {
		policy_tick(cache->policy, false);

		spin_lock_irqsave(&cache->lock, flags);
		cache->need_tick_bio = true;
		spin_unlock_irqrestore(&cache->lock, flags);
	}

	bio_drop_shared_lock(cache, bio);
	accounted_complete(cache, bio);

	return DM_ENDIO_DONE;
}