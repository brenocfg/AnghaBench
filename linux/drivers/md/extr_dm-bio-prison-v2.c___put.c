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
struct dm_bio_prison_v2 {int /*<<< orphan*/  cells; int /*<<< orphan*/  wq; } ;
struct dm_bio_prison_cell_v2 {int /*<<< orphan*/  node; int /*<<< orphan*/ * quiesce_continuation; scalar_t__ exclusive_lock; int /*<<< orphan*/  shared_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __put(struct dm_bio_prison_v2 *prison,
		  struct dm_bio_prison_cell_v2 *cell)
{
	BUG_ON(!cell->shared_count);
	cell->shared_count--;

	// FIXME: shared locks granted above the lock level could starve this
	if (!cell->shared_count) {
		if (cell->exclusive_lock){
			if (cell->quiesce_continuation) {
				queue_work(prison->wq, cell->quiesce_continuation);
				cell->quiesce_continuation = NULL;
			}
		} else {
			rb_erase(&cell->node, &prison->cells);
			return true;
		}
	}

	return false;
}