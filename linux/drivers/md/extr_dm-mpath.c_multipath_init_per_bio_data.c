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
struct dm_mpath_io {int /*<<< orphan*/ * pgpath; int /*<<< orphan*/  nr_bytes; } ;
struct dm_bio_details {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bio_record (struct dm_bio_details*,struct bio*) ; 
 struct dm_bio_details* get_bio_details_from_mpio (struct dm_mpath_io*) ; 
 struct dm_mpath_io* get_mpio_from_bio (struct bio*) ; 

__attribute__((used)) static void multipath_init_per_bio_data(struct bio *bio, struct dm_mpath_io **mpio_p)
{
	struct dm_mpath_io *mpio = get_mpio_from_bio(bio);
	struct dm_bio_details *bio_details = get_bio_details_from_mpio(mpio);

	mpio->nr_bytes = bio->bi_iter.bi_size;
	mpio->pgpath = NULL;
	*mpio_p = mpio;

	dm_bio_record(bio_details, bio);
}