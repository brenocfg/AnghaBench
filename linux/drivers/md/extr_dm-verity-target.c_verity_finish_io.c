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
struct dm_verity_io {int /*<<< orphan*/  orig_bi_end_io; struct dm_verity* v; } ;
struct dm_verity {TYPE_1__* ti; } ;
struct bio {int /*<<< orphan*/  bi_status; int /*<<< orphan*/  bi_end_io; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  per_io_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 struct bio* dm_bio_from_per_bio_data (struct dm_verity_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verity_fec_finish_io (struct dm_verity_io*) ; 

__attribute__((used)) static void verity_finish_io(struct dm_verity_io *io, blk_status_t status)
{
	struct dm_verity *v = io->v;
	struct bio *bio = dm_bio_from_per_bio_data(io, v->ti->per_io_data_size);

	bio->bi_end_io = io->orig_bi_end_io;
	bio->bi_status = status;

	verity_fec_finish_io(io);

	bio_endio(bio);
}