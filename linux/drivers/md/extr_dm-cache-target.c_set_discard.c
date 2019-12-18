#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  discard_count; } ;
struct cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  discard_bitset; TYPE_1__ stats; int /*<<< orphan*/  discard_nr_blocks; } ;
typedef  int /*<<< orphan*/  dm_dblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ from_dblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_discard(struct cache *cache, dm_dblock_t b)
{
	unsigned long flags;

	BUG_ON(from_dblock(b) >= from_dblock(cache->discard_nr_blocks));
	atomic_inc(&cache->stats.discard_count);

	spin_lock_irqsave(&cache->lock, flags);
	set_bit(from_dblock(b), cache->discard_bitset);
	spin_unlock_irqrestore(&cache->lock, flags);
}