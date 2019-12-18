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
struct thin_c {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_cells; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  (* process_cell ) (struct thin_c*,struct dm_bio_prison_cell*) ;int /*<<< orphan*/  (* process_discard_cell ) (struct thin_c*,struct dm_bio_prison_cell*) ;struct dm_bio_prison_cell** cell_sort_array; } ;
struct list_head {int dummy; } ;
struct dm_bio_prison_cell {int /*<<< orphan*/  holder; int /*<<< orphan*/  user_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ bio_op (int /*<<< orphan*/ ) ; 
 scalar_t__ ensure_next_mapping (struct pool*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 unsigned int sort_cells (struct pool*,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct thin_c*,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  stub2 (struct thin_c*,struct dm_bio_prison_cell*) ; 

__attribute__((used)) static void process_thin_deferred_cells(struct thin_c *tc)
{
	struct pool *pool = tc->pool;
	unsigned long flags;
	struct list_head cells;
	struct dm_bio_prison_cell *cell;
	unsigned i, j, count;

	INIT_LIST_HEAD(&cells);

	spin_lock_irqsave(&tc->lock, flags);
	list_splice_init(&tc->deferred_cells, &cells);
	spin_unlock_irqrestore(&tc->lock, flags);

	if (list_empty(&cells))
		return;

	do {
		count = sort_cells(tc->pool, &cells);

		for (i = 0; i < count; i++) {
			cell = pool->cell_sort_array[i];
			BUG_ON(!cell->holder);

			/*
			 * If we've got no free new_mapping structs, and processing
			 * this bio might require one, we pause until there are some
			 * prepared mappings to process.
			 */
			if (ensure_next_mapping(pool)) {
				for (j = i; j < count; j++)
					list_add(&pool->cell_sort_array[j]->user_list, &cells);

				spin_lock_irqsave(&tc->lock, flags);
				list_splice(&cells, &tc->deferred_cells);
				spin_unlock_irqrestore(&tc->lock, flags);
				return;
			}

			if (bio_op(cell->holder) == REQ_OP_DISCARD)
				pool->process_discard_cell(tc, cell);
			else
				pool->process_cell(tc, cell);
		}
	} while (!list_empty(&cells));
}