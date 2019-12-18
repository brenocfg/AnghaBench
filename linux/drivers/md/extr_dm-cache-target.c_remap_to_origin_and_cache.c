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
struct cache {int /*<<< orphan*/  bs; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  __remap_to_origin_clear_discard (struct cache*,struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remap_to_cache (struct cache*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void remap_to_origin_and_cache(struct cache *cache, struct bio *bio,
				      dm_oblock_t oblock, dm_cblock_t cblock)
{
	struct bio *origin_bio = bio_clone_fast(bio, GFP_NOIO, &cache->bs);

	BUG_ON(!origin_bio);

	bio_chain(origin_bio, bio);
	/*
	 * Passing false to __remap_to_origin_clear_discard() skips
	 * all code that might use per_bio_data (since clone doesn't have it)
	 */
	__remap_to_origin_clear_discard(cache, origin_bio, oblock, false);
	submit_bio(origin_bio);

	remap_to_cache(cache, bio, cblock);
}