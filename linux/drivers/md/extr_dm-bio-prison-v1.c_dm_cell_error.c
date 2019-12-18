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
struct dm_bio_prison_cell {int dummy; } ;
struct dm_bio_prison {int dummy; } ;
struct bio_list {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  dm_cell_release (struct dm_bio_prison*,struct dm_bio_prison_cell*,struct bio_list*) ; 

void dm_cell_error(struct dm_bio_prison *prison,
		   struct dm_bio_prison_cell *cell, blk_status_t error)
{
	struct bio_list bios;
	struct bio *bio;

	bio_list_init(&bios);
	dm_cell_release(prison, cell, &bios);

	while ((bio = bio_list_pop(&bios))) {
		bio->bi_status = error;
		bio_endio(bio);
	}
}