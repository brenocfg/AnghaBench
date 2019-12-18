#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sym_tcb {int dummy; } ;
struct sym_lcb {scalar_t__ started_max; scalar_t__ started_limit; int num_sgood; int /*<<< orphan*/  waiting_ccbq; } ;
struct sym_hcb {struct sym_tcb* target; } ;
struct TYPE_3__ {scalar_t__ lastp; } ;
struct TYPE_4__ {TYPE_1__ head; } ;
struct sym_ccb {scalar_t__ host_status; size_t target; scalar_t__ goalp; TYPE_2__ phys; int /*<<< orphan*/  lun; struct scsi_cmnd* cmd; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 scalar_t__ HS_COMPLETE ; 
 int /*<<< orphan*/  SYM_SETUP_RESIDUAL_SUPPORT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int sym_compute_residual (struct sym_hcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_free_ccb (struct sym_hcb*,struct sym_ccb*) ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_print_addr (struct scsi_cmnd*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sym_que_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_set_cam_result_ok (struct sym_ccb*,struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  sym_start_next_ccbs (struct sym_hcb*,struct sym_lcb*,int) ; 
 int sym_verbose ; 
 int /*<<< orphan*/  sym_xpt_done (struct sym_hcb*,struct scsi_cmnd*) ; 

void sym_complete_ok (struct sym_hcb *np, struct sym_ccb *cp)
{
	struct sym_tcb *tp;
	struct sym_lcb *lp;
	struct scsi_cmnd *cmd;
	int resid;

	/*
	 *  Paranoid check. :)
	 */
	if (!cp || !cp->cmd)
		return;
	assert (cp->host_status == HS_COMPLETE);

	/*
	 *  Get user command.
	 */
	cmd = cp->cmd;

	/*
	 *  Get target and lun pointers.
	 */
	tp = &np->target[cp->target];
	lp = sym_lp(tp, cp->lun);

	/*
	 *  If all data have been transferred, given than no
	 *  extended error did occur, there is no residual.
	 */
	resid = 0;
	if (cp->phys.head.lastp != cp->goalp)
		resid = sym_compute_residual(np, cp);

	/*
	 *  Wrong transfer residuals may be worse than just always 
	 *  returning zero. User can disable this feature in 
	 *  sym53c8xx.h. Residual support is enabled by default.
	 */
	if (!SYM_SETUP_RESIDUAL_SUPPORT)
		resid  = 0;
#ifdef DEBUG_2_0_X
if (resid)
	printf("XXXX RESID= %d - 0x%x\n", resid, resid);
#endif

	/*
	 *  Build result in CAM ccb.
	 */
	sym_set_cam_result_ok(cp, cmd, resid);

#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  If max number of started ccbs had been reduced,
	 *  increase it if 200 good status received.
	 */
	if (lp && lp->started_max < lp->started_limit) {
		++lp->num_sgood;
		if (lp->num_sgood >= 200) {
			lp->num_sgood = 0;
			++lp->started_max;
			if (sym_verbose >= 2) {
				sym_print_addr(cmd, " queue depth is now %d\n",
				       lp->started_max);
			}
		}
	}
#endif

	/*
	 *  Free our CCB.
	 */
	sym_free_ccb (np, cp);

#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Requeue a couple of awaiting scsi commands.
	 */
	if (!sym_que_empty(&lp->waiting_ccbq))
		sym_start_next_ccbs(np, lp, 2);
#endif
	/*
	 *  Complete the command.
	 */
	sym_xpt_done(np, cmd);
}