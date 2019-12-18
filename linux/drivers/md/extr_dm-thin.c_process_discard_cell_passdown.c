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
struct thin_c {int dummy; } ;
struct dm_thin_endio_hook {struct dm_bio_prison_cell* cell; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_end; int /*<<< orphan*/  block_begin; } ;
struct dm_bio_prison_cell {TYPE_1__ key; struct bio* holder; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  break_up_discard_bio (struct thin_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio*) ; 
 struct dm_thin_endio_hook* dm_per_bio_data (struct bio*,int) ; 

__attribute__((used)) static void process_discard_cell_passdown(struct thin_c *tc, struct dm_bio_prison_cell *virt_cell)
{
	struct bio *bio = virt_cell->holder;
	struct dm_thin_endio_hook *h = dm_per_bio_data(bio, sizeof(struct dm_thin_endio_hook));

	/*
	 * The virt_cell will only get freed once the origin bio completes.
	 * This means it will remain locked while all the individual
	 * passdown bios are in flight.
	 */
	h->cell = virt_cell;
	break_up_discard_bio(tc, virt_cell->key.block_begin, virt_cell->key.block_end, bio);

	/*
	 * We complete the bio now, knowing that the bi_remaining field
	 * will prevent completion until the sub range discards have
	 * completed.
	 */
	bio_endio(bio);
}