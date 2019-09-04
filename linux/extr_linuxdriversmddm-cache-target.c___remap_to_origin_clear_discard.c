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

/* Variables and functions */
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  check_if_tick_bio_needed (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  clear_discard (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oblock_to_dblock (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_origin (struct cache*,struct bio*) ; 

__attribute__((used)) static void __remap_to_origin_clear_discard(struct cache *cache, struct bio *bio,
					    dm_oblock_t oblock, bool bio_has_pbd)
{
	if (bio_has_pbd)
		check_if_tick_bio_needed(cache, bio);
	remap_to_origin(cache, bio);
	if (bio_data_dir(bio) == WRITE)
		clear_discard(cache, oblock_to_dblock(cache, oblock));
}