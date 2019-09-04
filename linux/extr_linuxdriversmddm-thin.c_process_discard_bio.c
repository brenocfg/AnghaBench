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
struct thin_c {TYPE_1__* pool; int /*<<< orphan*/  td; } ;
struct dm_cell_key {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* process_discard_cell ) (struct thin_c*,struct dm_bio_prison_cell*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTUAL ; 
 scalar_t__ bio_detain (TYPE_1__*,struct dm_cell_key*,struct bio*,struct dm_bio_prison_cell**) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct dm_cell_key*) ; 
 int /*<<< orphan*/  get_bio_block_range (struct thin_c*,struct bio*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (struct thin_c*,struct dm_bio_prison_cell*) ; 

__attribute__((used)) static void process_discard_bio(struct thin_c *tc, struct bio *bio)
{
	dm_block_t begin, end;
	struct dm_cell_key virt_key;
	struct dm_bio_prison_cell *virt_cell;

	get_bio_block_range(tc, bio, &begin, &end);
	if (begin == end) {
		/*
		 * The discard covers less than a block.
		 */
		bio_endio(bio);
		return;
	}

	build_key(tc->td, VIRTUAL, begin, end, &virt_key);
	if (bio_detain(tc->pool, &virt_key, bio, &virt_cell))
		/*
		 * Potential starvation issue: We're relying on the
		 * fs/application being well behaved, and not trying to
		 * send IO to a region at the same time as discarding it.
		 * If they do this persistently then it's possible this
		 * cell will never be granted.
		 */
		return;

	tc->pool->process_discard_cell(tc, virt_cell);
}