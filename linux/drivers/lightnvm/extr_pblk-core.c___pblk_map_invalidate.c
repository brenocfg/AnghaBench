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
typedef  int /*<<< orphan*/  u64 ;
struct pblk_line_mgmt {int /*<<< orphan*/  gc_lock; } ;
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  vsc; int /*<<< orphan*/  invalid_bitmap; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ PBLK_LINESTATE_CLOSED ; 
 scalar_t__ PBLK_LINESTATE_FREE ; 
 scalar_t__ PBLK_LINESTATE_GC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct list_head* pblk_line_gc_list (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __pblk_map_invalidate(struct pblk *pblk, struct pblk_line *line,
			   u64 paddr)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct list_head *move_list = NULL;

	/* Lines being reclaimed (GC'ed) cannot be invalidated. Before the L2P
	 * table is modified with reclaimed sectors, a check is done to endure
	 * that newer updates are not overwritten.
	 */
	spin_lock(&line->lock);
	WARN_ON(line->state == PBLK_LINESTATE_FREE);

	if (test_and_set_bit(paddr, line->invalid_bitmap)) {
		WARN_ONCE(1, "pblk: double invalidate\n");
		spin_unlock(&line->lock);
		return;
	}
	le32_add_cpu(line->vsc, -1);

	if (line->state == PBLK_LINESTATE_CLOSED)
		move_list = pblk_line_gc_list(pblk, line);
	spin_unlock(&line->lock);

	if (move_list) {
		spin_lock(&l_mg->gc_lock);
		spin_lock(&line->lock);
		/* Prevent moving a line that has just been chosen for GC */
		if (line->state == PBLK_LINESTATE_GC) {
			spin_unlock(&line->lock);
			spin_unlock(&l_mg->gc_lock);
			return;
		}
		spin_unlock(&line->lock);

		list_move_tail(&line->list, move_list);
		spin_unlock(&l_mg->gc_lock);
	}
}