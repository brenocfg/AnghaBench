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
struct pblk_line_mgmt {int /*<<< orphan*/  gc_lock; } ;
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  gc_group; int /*<<< orphan*/  id; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_LINEGC_NONE ; 
 scalar_t__ PBLK_LINESTATE_CLOSED ; 
 scalar_t__ PBLK_LINESTATE_GC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 struct list_head* pblk_line_gc_list (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_line_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void pblk_put_line_back(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct list_head *move_list;

	spin_lock(&l_mg->gc_lock);
	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_GC);
	line->state = PBLK_LINESTATE_CLOSED;
	trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);

	/* We need to reset gc_group in order to ensure that
	 * pblk_line_gc_list will return proper move_list
	 * since right now current line is not on any of the
	 * gc lists.
	 */
	line->gc_group = PBLK_LINEGC_NONE;
	move_list = pblk_line_gc_list(pblk, line);
	spin_unlock(&line->lock);
	list_add_tail(&line->list, move_list);
	spin_unlock(&l_mg->gc_lock);
}