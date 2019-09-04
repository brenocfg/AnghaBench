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
struct dm_bio_prison_cell_v2 {unsigned int exclusive_level; int shared_count; int /*<<< orphan*/  bios; scalar_t__ exclusive_lock; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ __find_or_insert (struct dm_bio_prison_v2*,struct dm_cell_key_v2*,struct dm_bio_prison_cell_v2*,struct dm_bio_prison_cell_v2**) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 

__attribute__((used)) static bool __get(struct dm_bio_prison_v2 *prison,
		  struct dm_cell_key_v2 *key,
		  unsigned lock_level,
		  struct bio *inmate,
		  struct dm_bio_prison_cell_v2 *cell_prealloc,
		  struct dm_bio_prison_cell_v2 **cell)
{
	if (__find_or_insert(prison, key, cell_prealloc, cell)) {
		if ((*cell)->exclusive_lock) {
			if (lock_level <= (*cell)->exclusive_level) {
				bio_list_add(&(*cell)->bios, inmate);
				return false;
			}
		}

		(*cell)->shared_count++;

	} else
		(*cell)->shared_count = 1;

	return true;
}