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
struct mirror_set {int /*<<< orphan*/  rh; } ;
struct mirror {int /*<<< orphan*/  error_count; } ;
struct bio_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 struct mirror* choose_mirror (struct mirror_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_bio_to_region (int /*<<< orphan*/ ,struct bio*) ; 
 struct mirror* get_default_mirror (struct mirror_set*) ; 
 scalar_t__ likely (struct mirror*) ; 
 int /*<<< orphan*/  read_async_bio (struct mirror*,struct bio*) ; 
 struct mirror* region_in_sync (struct mirror_set*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_reads(struct mirror_set *ms, struct bio_list *reads)
{
	region_t region;
	struct bio *bio;
	struct mirror *m;

	while ((bio = bio_list_pop(reads))) {
		region = dm_rh_bio_to_region(ms->rh, bio);
		m = get_default_mirror(ms);

		/*
		 * We can only read balance if the region is in sync.
		 */
		if (likely(region_in_sync(ms, region, 1)))
			m = choose_mirror(ms, bio->bi_iter.bi_sector);
		else if (m && atomic_read(&m->error_count))
			m = NULL;

		if (likely(m))
			read_async_bio(m, bio);
		else
			bio_io_error(bio);
	}
}