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
struct thin_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  mapping_pool; int /*<<< orphan*/  pmd; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/  cell; int /*<<< orphan*/  bio; scalar_t__ virt_begin; scalar_t__ virt_end; scalar_t__ data_block; struct thin_c* tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_io_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_defer_no_holder (struct thin_c*,int /*<<< orphan*/ ) ; 
 int dm_pool_dec_data_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mempool_free (struct dm_thin_new_mapping*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct pool*,char*,int) ; 

__attribute__((used)) static void process_prepared_discard_passdown_pt2(struct dm_thin_new_mapping *m)
{
	int r;
	struct thin_c *tc = m->tc;
	struct pool *pool = tc->pool;

	/*
	 * The passdown has completed, so now we can decrement all those
	 * unmapped blocks.
	 */
	r = dm_pool_dec_data_range(pool->pmd, m->data_block,
				   m->data_block + (m->virt_end - m->virt_begin));
	if (r) {
		metadata_operation_failed(pool, "dm_pool_dec_data_range", r);
		bio_io_error(m->bio);
	} else
		bio_endio(m->bio);

	cell_defer_no_holder(tc, m->cell);
	mempool_free(m, &pool->mapping_pool);
}