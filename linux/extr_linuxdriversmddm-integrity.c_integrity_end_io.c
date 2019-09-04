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
struct dm_integrity_io {scalar_t__ completion; int /*<<< orphan*/  orig_bi_end_io; scalar_t__ orig_bi_integrity; int /*<<< orphan*/  orig_bi_partno; int /*<<< orphan*/  orig_bi_disk; int /*<<< orphan*/  orig_bi_iter; } ;
struct bio {int /*<<< orphan*/  bi_end_io; int /*<<< orphan*/  bi_opf; scalar_t__ bi_integrity; int /*<<< orphan*/  bi_partno; int /*<<< orphan*/  bi_disk; int /*<<< orphan*/  bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_INTEGRITY ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  dec_in_flight (struct dm_integrity_io*) ; 
 struct dm_integrity_io* dm_per_bio_data (struct bio*,int) ; 

__attribute__((used)) static void integrity_end_io(struct bio *bio)
{
	struct dm_integrity_io *dio = dm_per_bio_data(bio, sizeof(struct dm_integrity_io));

	bio->bi_iter = dio->orig_bi_iter;
	bio->bi_disk = dio->orig_bi_disk;
	bio->bi_partno = dio->orig_bi_partno;
	if (dio->orig_bi_integrity) {
		bio->bi_integrity = dio->orig_bi_integrity;
		bio->bi_opf |= REQ_INTEGRITY;
	}
	bio->bi_end_io = dio->orig_bi_end_io;

	if (dio->completion)
		complete(dio->completion);

	dec_in_flight(dio);
}