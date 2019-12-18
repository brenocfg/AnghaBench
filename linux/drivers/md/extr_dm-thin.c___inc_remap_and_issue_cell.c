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
struct remap_info {int /*<<< orphan*/  issue_bios; TYPE_1__* tc; int /*<<< orphan*/  defer_bios; } ;
struct dm_bio_prison_cell {int /*<<< orphan*/  bios; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_DISCARD ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  inc_all_io_entry (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ op_is_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __inc_remap_and_issue_cell(void *context,
				       struct dm_bio_prison_cell *cell)
{
	struct remap_info *info = context;
	struct bio *bio;

	while ((bio = bio_list_pop(&cell->bios))) {
		if (op_is_flush(bio->bi_opf) || bio_op(bio) == REQ_OP_DISCARD)
			bio_list_add(&info->defer_bios, bio);
		else {
			inc_all_io_entry(info->tc->pool, bio);

			/*
			 * We can't issue the bios with the bio prison lock
			 * held, so we add them to a list to issue on
			 * return from this function.
			 */
			bio_list_add(&info->issue_bios, bio);
		}
	}
}