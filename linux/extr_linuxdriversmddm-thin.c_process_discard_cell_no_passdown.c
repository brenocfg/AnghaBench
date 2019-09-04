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
struct thin_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  (* process_prepared_discard ) (struct dm_thin_new_mapping*) ;int /*<<< orphan*/  all_io_ds; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/  list; int /*<<< orphan*/  bio; struct dm_bio_prison_cell* cell; int /*<<< orphan*/  virt_end; int /*<<< orphan*/  virt_begin; struct thin_c* tc; } ;
struct TYPE_2__ {int /*<<< orphan*/  block_end; int /*<<< orphan*/  block_begin; } ;
struct dm_bio_prison_cell {int /*<<< orphan*/  holder; TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_deferred_set_add_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dm_thin_new_mapping* get_next_mapping (struct pool*) ; 
 int /*<<< orphan*/  stub1 (struct dm_thin_new_mapping*) ; 

__attribute__((used)) static void process_discard_cell_no_passdown(struct thin_c *tc,
					     struct dm_bio_prison_cell *virt_cell)
{
	struct pool *pool = tc->pool;
	struct dm_thin_new_mapping *m = get_next_mapping(pool);

	/*
	 * We don't need to lock the data blocks, since there's no
	 * passdown.  We only lock data blocks for allocation and breaking sharing.
	 */
	m->tc = tc;
	m->virt_begin = virt_cell->key.block_begin;
	m->virt_end = virt_cell->key.block_end;
	m->cell = virt_cell;
	m->bio = virt_cell->holder;

	if (!dm_deferred_set_add_work(pool->all_io_ds, &m->list))
		pool->process_prepared_discard(m);
}