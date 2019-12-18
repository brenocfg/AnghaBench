#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thin_c {struct pool* pool; int /*<<< orphan*/  td; } ;
struct pool {int /*<<< orphan*/  mapping_pool; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/  list; int /*<<< orphan*/  data_block; TYPE_1__* cell; int /*<<< orphan*/  virt_begin; scalar_t__ status; struct bio* bio; struct thin_c* tc; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  holder; } ;

/* Variables and functions */
 int /*<<< orphan*/  cell_error (struct pool*,TYPE_1__*) ; 
 int /*<<< orphan*/  complete_overwrite_bio (struct thin_c*,struct bio*) ; 
 int dm_thin_insert_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_all_io_entry (struct pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_remap_and_issue_cell (struct thin_c*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct dm_thin_new_mapping*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct pool*,char*,int) ; 
 int /*<<< orphan*/  remap_and_issue (struct thin_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_prepared_mapping(struct dm_thin_new_mapping *m)
{
	struct thin_c *tc = m->tc;
	struct pool *pool = tc->pool;
	struct bio *bio = m->bio;
	int r;

	if (m->status) {
		cell_error(pool, m->cell);
		goto out;
	}

	/*
	 * Commit the prepared block into the mapping btree.
	 * Any I/O for this block arriving after this point will get
	 * remapped to it directly.
	 */
	r = dm_thin_insert_block(tc->td, m->virt_begin, m->data_block);
	if (r) {
		metadata_operation_failed(pool, "dm_thin_insert_block", r);
		cell_error(pool, m->cell);
		goto out;
	}

	/*
	 * Release any bios held while the block was being provisioned.
	 * If we are processing a write bio that completely covers the block,
	 * we already processed it so can ignore it now when processing
	 * the bios in the cell.
	 */
	if (bio) {
		inc_remap_and_issue_cell(tc, m->cell, m->data_block);
		complete_overwrite_bio(tc, bio);
	} else {
		inc_all_io_entry(tc->pool, m->cell->holder);
		remap_and_issue(tc, m->cell->holder, m->data_block);
		inc_remap_and_issue_cell(tc, m->cell, m->data_block);
	}

out:
	list_del(&m->list);
	mempool_free(m, &pool->mapping_pool);
}