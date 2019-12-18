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
struct pblk_line_mgmt {int /*<<< orphan*/  gc_lock; struct list_head** gc_lists; } ;
struct pblk_line {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct pblk_gc {int /*<<< orphan*/  read_inflight_gc; int /*<<< orphan*/  r_lock; int /*<<< orphan*/  r_list; } ;
struct TYPE_2__ {int rb_state; } ;
struct pblk {TYPE_1__ rl; struct pblk_gc gc; struct pblk_line_mgmt l_mg; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int PBLK_GC_L_QD ; 
 int PBLK_GC_NR_LISTS ; 
 scalar_t__ PBLK_LINESTATE_CLOSED ; 
 scalar_t__ PBLK_LINESTATE_GC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_gc_free_full_lines (struct pblk*) ; 
 struct pblk_line* pblk_gc_get_victim_line (struct pblk*,struct list_head*) ; 
 int /*<<< orphan*/  pblk_gc_reader_kick (struct pblk_gc*) ; 
 int pblk_gc_should_run (struct pblk_gc*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_line_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pblk_gc_run(struct pblk *pblk)
{
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_gc *gc = &pblk->gc;
	struct pblk_line *line;
	struct list_head *group_list;
	bool run_gc;
	int read_inflight_gc, gc_group = 0, prev_group = 0;

	pblk_gc_free_full_lines(pblk);

	run_gc = pblk_gc_should_run(&pblk->gc, &pblk->rl);
	if (!run_gc || (atomic_read(&gc->read_inflight_gc) >= PBLK_GC_L_QD))
		return;

next_gc_group:
	group_list = l_mg->gc_lists[gc_group++];

	do {
		spin_lock(&l_mg->gc_lock);

		line = pblk_gc_get_victim_line(pblk, group_list);
		if (!line) {
			spin_unlock(&l_mg->gc_lock);
			break;
		}

		spin_lock(&line->lock);
		WARN_ON(line->state != PBLK_LINESTATE_CLOSED);
		line->state = PBLK_LINESTATE_GC;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);
		spin_unlock(&line->lock);

		list_del(&line->list);
		spin_unlock(&l_mg->gc_lock);

		spin_lock(&gc->r_lock);
		list_add_tail(&line->list, &gc->r_list);
		spin_unlock(&gc->r_lock);

		read_inflight_gc = atomic_inc_return(&gc->read_inflight_gc);
		pblk_gc_reader_kick(gc);

		prev_group = 1;

		/* No need to queue up more GC lines than we can handle */
		run_gc = pblk_gc_should_run(&pblk->gc, &pblk->rl);
		if (!run_gc || read_inflight_gc >= PBLK_GC_L_QD)
			break;
	} while (1);

	if (!prev_group && pblk->rl.rb_state > gc_group &&
						gc_group < PBLK_GC_NR_LISTS)
		goto next_gc_group;
}