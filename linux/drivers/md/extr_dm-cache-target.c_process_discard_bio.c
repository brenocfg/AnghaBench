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
struct TYPE_2__ {scalar_t__ discard_passdown; } ;
struct cache {TYPE_1__ features; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ dm_dblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  calc_discard_block_range (struct cache*,struct bio*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ from_dblock (scalar_t__) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  remap_to_origin (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  set_discard (struct cache*,scalar_t__) ; 
 scalar_t__ to_dblock (scalar_t__) ; 

__attribute__((used)) static bool process_discard_bio(struct cache *cache, struct bio *bio)
{
	dm_dblock_t b, e;

	// FIXME: do we need to lock the region?  Or can we just assume the
	// user wont be so foolish as to issue discard concurrently with
	// other IO?
	calc_discard_block_range(cache, bio, &b, &e);
	while (b != e) {
		set_discard(cache, b);
		b = to_dblock(from_dblock(b) + 1);
	}

	if (cache->features.discard_passdown) {
		remap_to_origin(cache, bio);
		generic_make_request(bio);
	} else
		bio_endio(bio);

	return false;
}