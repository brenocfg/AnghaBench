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
struct dm_clone_metadata {int /*<<< orphan*/  bitmap_lock; int /*<<< orphan*/  region_map; struct dirty_map* current_dmap; scalar_t__ read_only; } ;
struct dirty_map {int changed; int /*<<< orphan*/  dirty_words; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
 int EPERM ; 
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (unsigned long,int /*<<< orphan*/ ) ; 

int dm_clone_cond_set_range(struct dm_clone_metadata *cmd, unsigned long start,
			    unsigned long nr_regions)
{
	int r = 0;
	struct dirty_map *dmap;
	unsigned long word, region_nr, flags;

	spin_lock_irqsave(&cmd->bitmap_lock, flags);

	if (cmd->read_only) {
		r = -EPERM;
		goto out;
	}

	dmap = cmd->current_dmap;
	for (region_nr = start; region_nr < (start + nr_regions); region_nr++) {
		if (!test_bit(region_nr, cmd->region_map)) {
			word = region_nr / BITS_PER_LONG;
			__set_bit(word, dmap->dirty_words);
			__set_bit(region_nr, cmd->region_map);
			dmap->changed = 1;
		}
	}
out:
	spin_unlock_irqrestore(&cmd->bitmap_lock, flags);

	return r;
}