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
struct TYPE_2__ {scalar_t__ zero_new_blocks; } ;
struct pool {int sectors_per_block; TYPE_1__ pf; } ;
struct dm_thin_new_mapping {int virt_begin; int virt_end; int data_block; struct dm_bio_prison_cell* cell; struct thin_c* tc; int /*<<< orphan*/  prepare_actions; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio {int dummy; } ;
typedef  int dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct dm_thin_new_mapping* get_next_mapping (struct pool*) ; 
 scalar_t__ io_overwrites_block (struct pool*,struct bio*) ; 
 int /*<<< orphan*/  ll_zero (struct thin_c*,struct dm_thin_new_mapping*,int,int) ; 
 int /*<<< orphan*/  process_prepared_mapping (struct dm_thin_new_mapping*) ; 
 int /*<<< orphan*/  remap_and_issue_overwrite (struct thin_c*,struct bio*,int,struct dm_thin_new_mapping*) ; 

__attribute__((used)) static void schedule_zero(struct thin_c *tc, dm_block_t virt_block,
			  dm_block_t data_block, struct dm_bio_prison_cell *cell,
			  struct bio *bio)
{
	struct pool *pool = tc->pool;
	struct dm_thin_new_mapping *m = get_next_mapping(pool);

	atomic_set(&m->prepare_actions, 1); /* no need to quiesce */
	m->tc = tc;
	m->virt_begin = virt_block;
	m->virt_end = virt_block + 1u;
	m->data_block = data_block;
	m->cell = cell;

	/*
	 * If the whole block of data is being overwritten or we are not
	 * zeroing pre-existing data, we can issue the bio immediately.
	 * Otherwise we use kcopyd to zero the data first.
	 */
	if (pool->pf.zero_new_blocks) {
		if (io_overwrites_block(pool, bio))
			remap_and_issue_overwrite(tc, bio, data_block, m);
		else
			ll_zero(tc, m, data_block * pool->sectors_per_block,
				(data_block + 1) * pool->sectors_per_block);
	} else
		process_prepared_mapping(m);
}