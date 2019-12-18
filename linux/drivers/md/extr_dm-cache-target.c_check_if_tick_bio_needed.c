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
struct per_bio_data {int tick; } ;
struct cache {int need_tick_bio; int /*<<< orphan*/  lock; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ bio_op (struct bio*) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  op_is_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void check_if_tick_bio_needed(struct cache *cache, struct bio *bio)
{
	unsigned long flags;
	struct per_bio_data *pb;

	spin_lock_irqsave(&cache->lock, flags);
	if (cache->need_tick_bio && !op_is_flush(bio->bi_opf) &&
	    bio_op(bio) != REQ_OP_DISCARD) {
		pb = get_per_bio_data(bio);
		pb->tick = true;
		cache->need_tick_bio = false;
	}
	spin_unlock_irqrestore(&cache->lock, flags);
}