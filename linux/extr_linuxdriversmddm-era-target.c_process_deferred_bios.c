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
struct bio_list {int dummy; } ;
struct era {TYPE_1__* md; int /*<<< orphan*/  deferred_lock; struct bio_list deferred_bios; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_writeset; int /*<<< orphan*/  bitset_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  get_block (struct era*,struct bio*) ; 
 int metadata_commit (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int writeset_test_and_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_deferred_bios(struct era *era)
{
	int r;
	struct bio_list deferred_bios, marked_bios;
	struct bio *bio;
	bool commit_needed = false;
	bool failed = false;

	bio_list_init(&deferred_bios);
	bio_list_init(&marked_bios);

	spin_lock(&era->deferred_lock);
	bio_list_merge(&deferred_bios, &era->deferred_bios);
	bio_list_init(&era->deferred_bios);
	spin_unlock(&era->deferred_lock);

	while ((bio = bio_list_pop(&deferred_bios))) {
		r = writeset_test_and_set(&era->md->bitset_info,
					  era->md->current_writeset,
					  get_block(era, bio));
		if (r < 0) {
			/*
			 * This is bad news, we need to rollback.
			 * FIXME: finish.
			 */
			failed = true;

		} else if (r == 0)
			commit_needed = true;

		bio_list_add(&marked_bios, bio);
	}

	if (commit_needed) {
		r = metadata_commit(era->md);
		if (r)
			failed = true;
	}

	if (failed)
		while ((bio = bio_list_pop(&marked_bios)))
			bio_io_error(bio);
	else
		while ((bio = bio_list_pop(&marked_bios)))
			generic_make_request(bio);
}