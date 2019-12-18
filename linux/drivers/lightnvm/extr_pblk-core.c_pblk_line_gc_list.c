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
struct list_head {int dummy; } ;
struct pblk_line_mgmt {struct list_head corrupt_list; struct list_head gc_empty_list; struct list_head gc_low_list; struct list_head gc_mid_list; struct list_head gc_high_list; struct list_head gc_full_list; struct list_head gc_werr_list; } ;
struct pblk_line_meta {int high_thrs; int mid_thrs; } ;
struct pblk_line {scalar_t__ gc_group; int sec_in_line; int /*<<< orphan*/  id; int /*<<< orphan*/  state; TYPE_1__* w_err_gc; int /*<<< orphan*/  lock; int /*<<< orphan*/ * vsc; } ;
struct pblk {int min_write_pgs_data; int min_write_pgs; int /*<<< orphan*/  rl; struct pblk_line_mgmt l_mg; struct pblk_line_meta lm; } ;
struct TYPE_2__ {scalar_t__ has_write_err; } ;

/* Variables and functions */
 scalar_t__ PBLK_LINEGC_EMPTY ; 
 scalar_t__ PBLK_LINEGC_FULL ; 
 scalar_t__ PBLK_LINEGC_HIGH ; 
 scalar_t__ PBLK_LINEGC_LOW ; 
 scalar_t__ PBLK_LINEGC_MID ; 
 scalar_t__ PBLK_LINEGC_NONE ; 
 scalar_t__ PBLK_LINEGC_WERR ; 
 int /*<<< orphan*/  PBLK_LINESTATE_CORRUPT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  pblk_rl_werr_line_in (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_pblk_line_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct list_head *pblk_line_gc_list(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_line_meta *lm = &pblk->lm;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct list_head *move_list = NULL;
	int packed_meta = (le32_to_cpu(*line->vsc) / pblk->min_write_pgs_data)
			* (pblk->min_write_pgs - pblk->min_write_pgs_data);
	int vsc = le32_to_cpu(*line->vsc) + packed_meta;

	lockdep_assert_held(&line->lock);

	if (line->w_err_gc->has_write_err) {
		if (line->gc_group != PBLK_LINEGC_WERR) {
			line->gc_group = PBLK_LINEGC_WERR;
			move_list = &l_mg->gc_werr_list;
			pblk_rl_werr_line_in(&pblk->rl);
		}
	} else if (!vsc) {
		if (line->gc_group != PBLK_LINEGC_FULL) {
			line->gc_group = PBLK_LINEGC_FULL;
			move_list = &l_mg->gc_full_list;
		}
	} else if (vsc < lm->high_thrs) {
		if (line->gc_group != PBLK_LINEGC_HIGH) {
			line->gc_group = PBLK_LINEGC_HIGH;
			move_list = &l_mg->gc_high_list;
		}
	} else if (vsc < lm->mid_thrs) {
		if (line->gc_group != PBLK_LINEGC_MID) {
			line->gc_group = PBLK_LINEGC_MID;
			move_list = &l_mg->gc_mid_list;
		}
	} else if (vsc < line->sec_in_line) {
		if (line->gc_group != PBLK_LINEGC_LOW) {
			line->gc_group = PBLK_LINEGC_LOW;
			move_list = &l_mg->gc_low_list;
		}
	} else if (vsc == line->sec_in_line) {
		if (line->gc_group != PBLK_LINEGC_EMPTY) {
			line->gc_group = PBLK_LINEGC_EMPTY;
			move_list = &l_mg->gc_empty_list;
		}
	} else {
		line->state = PBLK_LINESTATE_CORRUPT;
		trace_pblk_line_state(pblk_disk_name(pblk), line->id,
					line->state);

		line->gc_group = PBLK_LINEGC_NONE;
		move_list =  &l_mg->corrupt_list;
		pblk_err(pblk, "corrupted vsc for line %d, vsc:%d (%d/%d/%d)\n",
						line->id, vsc,
						line->sec_in_line,
						lm->high_thrs, lm->mid_thrs);
	}

	return move_list;
}