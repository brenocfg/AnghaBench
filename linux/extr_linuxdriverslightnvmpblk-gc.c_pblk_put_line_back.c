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
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct pblk {struct pblk_line_mgmt l_mg; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ PBLK_LINESTATE_CLOSED ; 
 scalar_t__ PBLK_LINESTATE_GC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct list_head* pblk_line_gc_list (struct pblk*,struct pblk_line*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_put_line_back(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct list_head *move_list;

	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_GC);
	line->state = PBLK_LINESTATE_CLOSED;
	move_list = pblk_line_gc_list(pblk, line);
	spin_unlock(&line->lock);

	if (move_list) {
		spin_lock(&l_mg->gc_lock);
		list_add_tail(&line->list, move_list);
		spin_unlock(&l_mg->gc_lock);
	}
}