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
struct dm_cell_key_v2 {int dummy; } ;
struct dm_bio_prison_v2 {int dummy; } ;
struct dm_bio_prison_cell_v2 {int exclusive_lock; unsigned int exclusive_level; scalar_t__ shared_count; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ __find_or_insert (struct dm_bio_prison_v2*,struct dm_cell_key_v2*,struct dm_bio_prison_cell_v2*,struct dm_bio_prison_cell_v2**) ; 

__attribute__((used)) static int __lock(struct dm_bio_prison_v2 *prison,
		  struct dm_cell_key_v2 *key,
		  unsigned lock_level,
		  struct dm_bio_prison_cell_v2 *cell_prealloc,
		  struct dm_bio_prison_cell_v2 **cell_result)
{
	struct dm_bio_prison_cell_v2 *cell;

	if (__find_or_insert(prison, key, cell_prealloc, &cell)) {
		if (cell->exclusive_lock)
			return -EBUSY;

		cell->exclusive_lock = true;
		cell->exclusive_level = lock_level;
		*cell_result = cell;

		// FIXME: we don't yet know what level these shared locks
		// were taken at, so have to quiesce them all.
		return cell->shared_count > 0;

	} else {
		cell = cell_prealloc;
		cell->shared_count = 0;
		cell->exclusive_lock = true;
		cell->exclusive_level = lock_level;
		*cell_result = cell;
	}

	return 0;
}