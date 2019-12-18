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
struct sym_tcb {struct sym_ccb* nego_cp; } ;
struct TYPE_2__ {void* resel_sa; void* itl_task_sa; } ;
struct sym_lcb {size_t* cb_tags; size_t if_tag; scalar_t__ busy_itlq; scalar_t__ busy_itl; int /*<<< orphan*/  started_no_tag; int /*<<< orphan*/  started_tags; TYPE_1__ head; void** itlq_tbl; int /*<<< orphan*/ * tags_sum; } ;
struct sym_hcb {int /*<<< orphan*/  dummy_ccbq; int /*<<< orphan*/  free_ccbq; struct sym_ccb* last_cp; int /*<<< orphan*/  bad_itl_ba; int /*<<< orphan*/  bad_itlq_ba; struct sym_tcb* target; } ;
struct sym_ccb {size_t target; size_t tag; size_t tags_si; scalar_t__ started; int /*<<< orphan*/  link2_ccbq; int /*<<< orphan*/  link_ccbq; int /*<<< orphan*/  host_status; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_TAGS ; 
 int /*<<< orphan*/  HS_IDLE ; 
 size_t NO_TAG ; 
 int /*<<< orphan*/  SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 size_t SYM_CONF_MAX_TASK ; 
 void* cpu_to_scr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resel_bad_lun ; 
 int /*<<< orphan*/  sym_insque_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_insque_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_print_addr (int /*<<< orphan*/ *,char*,struct sym_ccb*,size_t) ; 
 int /*<<< orphan*/  sym_remque (int /*<<< orphan*/ *) ; 

void sym_free_ccb (struct sym_hcb *np, struct sym_ccb *cp)
{
	struct sym_tcb *tp = &np->target[cp->target];
	struct sym_lcb *lp = sym_lp(tp, cp->lun);

	if (DEBUG_FLAGS & DEBUG_TAGS) {
		sym_print_addr(cp->cmd, "ccb @%p freeing tag %d.\n",
				cp, cp->tag);
	}

	/*
	 *  If LCB available,
	 */
	if (lp) {
		/*
		 *  If tagged, release the tag, set the relect path 
		 */
		if (cp->tag != NO_TAG) {
#ifdef SYM_OPT_LIMIT_COMMAND_REORDERING
			--lp->tags_sum[cp->tags_si];
#endif
			/*
			 *  Free the tag value.
			 */
			lp->cb_tags[lp->if_tag] = cp->tag;
			if (++lp->if_tag == SYM_CONF_MAX_TASK)
				lp->if_tag = 0;
			/*
			 *  Make the reselect path invalid, 
			 *  and uncount this CCB.
			 */
			lp->itlq_tbl[cp->tag] = cpu_to_scr(np->bad_itlq_ba);
			--lp->busy_itlq;
		} else {	/* Untagged */
			/*
			 *  Make the reselect path invalid, 
			 *  and uncount this CCB.
			 */
			lp->head.itl_task_sa = cpu_to_scr(np->bad_itl_ba);
			--lp->busy_itl;
		}
		/*
		 *  If no JOB active, make the LUN reselect path invalid.
		 */
		if (lp->busy_itlq == 0 && lp->busy_itl == 0)
			lp->head.resel_sa =
				cpu_to_scr(SCRIPTB_BA(np, resel_bad_lun));
	}

	/*
	 *  We donnot queue more than 1 ccb per target 
	 *  with negotiation at any time. If this ccb was 
	 *  used for negotiation, clear this info in the tcb.
	 */
	if (cp == tp->nego_cp)
		tp->nego_cp = NULL;

#ifdef SYM_CONF_IARB_SUPPORT
	/*
	 *  If we just complete the last queued CCB,
	 *  clear this info that is no longer relevant.
	 */
	if (cp == np->last_cp)
		np->last_cp = 0;
#endif

	/*
	 *  Make this CCB available.
	 */
	cp->cmd = NULL;
	cp->host_status = HS_IDLE;
	sym_remque(&cp->link_ccbq);
	sym_insque_head(&cp->link_ccbq, &np->free_ccbq);

#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
	if (lp) {
		sym_remque(&cp->link2_ccbq);
		sym_insque_tail(&cp->link2_ccbq, &np->dummy_ccbq);
		if (cp->started) {
			if (cp->tag != NO_TAG)
				--lp->started_tags;
			else
				--lp->started_no_tag;
		}
	}
	cp->started = 0;
#endif
}