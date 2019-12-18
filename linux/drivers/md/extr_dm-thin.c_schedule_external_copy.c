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
struct thin_c {scalar_t__ origin_size; int /*<<< orphan*/  origin_dev; struct pool* pool; } ;
struct pool {int sectors_per_block; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  int dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_copy (struct thin_c*,int,int /*<<< orphan*/ ,int,int,struct dm_bio_prison_cell*,struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  schedule_zero (struct thin_c*,int,int,struct dm_bio_prison_cell*,struct bio*) ; 

__attribute__((used)) static void schedule_external_copy(struct thin_c *tc, dm_block_t virt_block,
				   dm_block_t data_dest,
				   struct dm_bio_prison_cell *cell, struct bio *bio)
{
	struct pool *pool = tc->pool;
	sector_t virt_block_begin = virt_block * pool->sectors_per_block;
	sector_t virt_block_end = (virt_block + 1) * pool->sectors_per_block;

	if (virt_block_end <= tc->origin_size)
		schedule_copy(tc, virt_block, tc->origin_dev,
			      virt_block, data_dest, cell, bio,
			      pool->sectors_per_block);

	else if (virt_block_begin < tc->origin_size)
		schedule_copy(tc, virt_block, tc->origin_dev,
			      virt_block, data_dest, cell, bio,
			      tc->origin_size - virt_block_begin);

	else
		schedule_zero(tc, virt_block, data_dest, cell, bio);
}