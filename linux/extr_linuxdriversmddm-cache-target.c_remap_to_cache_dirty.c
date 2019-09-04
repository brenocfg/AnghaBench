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
struct cache {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  check_if_tick_bio_needed (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  clear_discard (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oblock_to_dblock (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_cache (struct cache*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dirty (struct cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remap_to_cache_dirty(struct cache *cache, struct bio *bio,
				 dm_oblock_t oblock, dm_cblock_t cblock)
{
	check_if_tick_bio_needed(cache, bio);
	remap_to_cache(cache, bio, cblock);
	if (bio_data_dir(bio) == WRITE) {
		set_dirty(cache, cblock);
		clear_discard(cache, oblock_to_dblock(cache, oblock));
	}
}