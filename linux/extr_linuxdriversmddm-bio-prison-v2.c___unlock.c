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
struct dm_bio_prison_v2 {int /*<<< orphan*/  cells; } ;
struct dm_bio_prison_cell_v2 {int /*<<< orphan*/  node; scalar_t__ exclusive_lock; scalar_t__ shared_count; int /*<<< orphan*/  bios; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __unlock(struct dm_bio_prison_v2 *prison,
		     struct dm_bio_prison_cell_v2 *cell,
		     struct bio_list *bios)
{
	BUG_ON(!cell->exclusive_lock);

	bio_list_merge(bios, &cell->bios);
	bio_list_init(&cell->bios);

	if (cell->shared_count) {
		cell->exclusive_lock = 0;
		return false;
	}

	rb_erase(&cell->node, &prison->cells);
	return true;
}