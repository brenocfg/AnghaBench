#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pblk_line_mgmt {int /*<<< orphan*/  free_lock; int /*<<< orphan*/  nr_free_lines; int /*<<< orphan*/  free_list; } ;
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; TYPE_1__* w_err_gc; int /*<<< orphan*/  gc_group; } ;
struct pblk_gc {int /*<<< orphan*/  pipeline_gc; } ;
struct pblk {int /*<<< orphan*/  rl; struct pblk_gc gc; struct pblk_line_mgmt l_mg; } ;
struct TYPE_2__ {scalar_t__ has_write_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_LINEGC_NONE ; 
 scalar_t__ PBLK_LINESTATE_FREE ; 
 scalar_t__ PBLK_LINESTATE_GC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_line_free (struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_rl_free_lines_inc (int /*<<< orphan*/ *,struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_rl_werr_line_out (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __pblk_line_put(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_gc *gc = &pblk->gc;

	spin_lock(&line->lock);
	WARN_ON(line->state != PBLK_LINESTATE_GC);
	line->state = PBLK_LINESTATE_FREE;
	line->gc_group = PBLK_LINEGC_NONE;
	pblk_line_free(line);

	if (line->w_err_gc->has_write_err) {
		pblk_rl_werr_line_out(&pblk->rl);
		line->w_err_gc->has_write_err = 0;
	}

	spin_unlock(&line->lock);
	atomic_dec(&gc->pipeline_gc);

	spin_lock(&l_mg->free_lock);
	list_add_tail(&line->list, &l_mg->free_list);
	l_mg->nr_free_lines++;
	spin_unlock(&l_mg->free_lock);

	pblk_rl_free_lines_inc(&pblk->rl, line);
}