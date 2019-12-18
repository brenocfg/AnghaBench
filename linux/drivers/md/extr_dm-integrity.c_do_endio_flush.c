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
struct dm_integrity_io {int /*<<< orphan*/  fua; } ;
struct dm_integrity_c {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 struct bio* dm_bio_from_per_bio_data (struct dm_integrity_io*,int) ; 
 int /*<<< orphan*/  dm_integrity_failed (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  do_endio (struct dm_integrity_c*,struct bio*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  submit_flush_bio (struct dm_integrity_c*,struct dm_integrity_io*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_endio_flush(struct dm_integrity_c *ic, struct dm_integrity_io *dio)
{
	struct bio *bio = dm_bio_from_per_bio_data(dio, sizeof(struct dm_integrity_io));

	if (unlikely(dio->fua) && likely(!bio->bi_status) && likely(!dm_integrity_failed(ic)))
		submit_flush_bio(ic, dio);
	else
		do_endio(ic, bio);
}