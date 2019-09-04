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
struct bio {int /*<<< orphan*/ * bi_private; int /*<<< orphan*/ * bi_end_io; } ;
struct TYPE_2__ {struct bio bio; } ;
struct search {int /*<<< orphan*/  cl; TYPE_1__ bio; } ;
typedef  int /*<<< orphan*/  bio_end_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  __bio_clone_fast (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_cnt_set (struct bio*,int) ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_bio_hook(struct search *s,
			struct bio *orig_bio,
			bio_end_io_t *end_io_fn)
{
	struct bio *bio = &s->bio.bio;

	bio_init(bio, NULL, 0);
	__bio_clone_fast(bio, orig_bio);
	/*
	 * bi_end_io can be set separately somewhere else, e.g. the
	 * variants in,
	 * - cache_bio->bi_end_io from cached_dev_cache_miss()
	 * - n->bi_end_io from cache_lookup_fn()
	 */
	bio->bi_end_io		= end_io_fn;
	bio->bi_private		= &s->cl;

	bio_cnt_set(bio, 3);
}