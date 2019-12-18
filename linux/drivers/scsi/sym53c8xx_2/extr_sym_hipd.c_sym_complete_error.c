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
struct sym_tcb {int dummy; } ;
struct sym_lcb {int started_tags; int started_max; scalar_t__ num_sgood; } ;
struct sym_hcb {int squeue_ba; int /*<<< orphan*/  comp_ccbq; struct sym_tcb* target; } ;
struct sym_ccb {size_t target; int /*<<< orphan*/  link_ccbq; int /*<<< orphan*/  ssss_status; int /*<<< orphan*/  host_status; scalar_t__ sv_resid; int /*<<< orphan*/  xerr_status; int /*<<< orphan*/  host_flags; struct scsi_cmnd* cmd; } ;
struct scsi_device {int /*<<< orphan*/  lun; int /*<<< orphan*/  sdev_gendev; } ;
struct scsi_cmnd {struct scsi_device* device; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_RESULT ; 
 int DEBUG_TINY ; 
 int /*<<< orphan*/  DID_SOFT_ERROR ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_COMPLETE ; 
 int /*<<< orphan*/  HS_COMP_ERR ; 
 int INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYM_SETUP_RESIDUAL_SUPPORT ; 
 int /*<<< orphan*/  S_ILLEGAL ; 
 int /*<<< orphan*/  S_QUEUE_FULL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct sym_ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nc_scratcha ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  start ; 
 int sym_compute_residual (struct sym_hcb*,struct sym_ccb*) ; 
 int sym_dequeue_from_squeue (struct sym_hcb*,int,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sym_flush_comp_queue (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_insque_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_print_addr (struct scsi_cmnd*,char*,int) ; 
 int /*<<< orphan*/  sym_print_xerr (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_remque (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_set_cam_result_error (struct sym_hcb*,struct sym_ccb*,int) ; 
 int /*<<< orphan*/  sym_set_cam_status (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_start_next_ccbs (struct sym_hcb*,struct sym_lcb*,int) ; 
 int sym_verbose ; 

void sym_complete_error(struct sym_hcb *np, struct sym_ccb *cp)
{
	struct scsi_device *sdev;
	struct scsi_cmnd *cmd;
	struct sym_tcb *tp;
	struct sym_lcb *lp;
	int resid;
	int i;

	/*
	 *  Paranoid check. :)
	 */
	if (!cp || !cp->cmd)
		return;

	cmd = cp->cmd;
	sdev = cmd->device;
	if (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_RESULT)) {
		dev_info(&sdev->sdev_gendev, "CCB=%p STAT=%x/%x/%x\n", cp,
			cp->host_status, cp->ssss_status, cp->host_flags);
	}

	/*
	 *  Get target and lun pointers.
	 */
	tp = &np->target[cp->target];
	lp = sym_lp(tp, sdev->lun);

	/*
	 *  Check for extended errors.
	 */
	if (cp->xerr_status) {
		if (sym_verbose)
			sym_print_xerr(cmd, cp->xerr_status);
		if (cp->host_status == HS_COMPLETE)
			cp->host_status = HS_COMP_ERR;
	}

	/*
	 *  Calculate the residual.
	 */
	resid = sym_compute_residual(np, cp);

	if (!SYM_SETUP_RESIDUAL_SUPPORT) {/* If user does not want residuals */
		resid  = 0;		 /* throw them away. :)		    */
		cp->sv_resid = 0;
	}
#ifdef DEBUG_2_0_X
if (resid)
	printf("XXXX RESID= %d - 0x%x\n", resid, resid);
#endif

	/*
	 *  Dequeue all queued CCBs for that device 
	 *  not yet started by SCRIPTS.
	 */
	i = (INL(np, nc_scratcha) - np->squeue_ba) / 4;
	i = sym_dequeue_from_squeue(np, i, cp->target, sdev->lun, -1);

	/*
	 *  Restart the SCRIPTS processor.
	 */
	OUTL_DSP(np, SCRIPTA_BA(np, start));

#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
	if (cp->host_status == HS_COMPLETE &&
	    cp->ssss_status == S_QUEUE_FULL) {
		if (!lp || lp->started_tags - i < 2)
			goto weirdness;
		/*
		 *  Decrease queue depth as needed.
		 */
		lp->started_max = lp->started_tags - i - 1;
		lp->num_sgood = 0;

		if (sym_verbose >= 2) {
			sym_print_addr(cmd, " queue depth is now %d\n",
					lp->started_max);
		}

		/*
		 *  Repair the CCB.
		 */
		cp->host_status = HS_BUSY;
		cp->ssss_status = S_ILLEGAL;

		/*
		 *  Let's requeue it to device.
		 */
		sym_set_cam_status(cmd, DID_SOFT_ERROR);
		goto finish;
	}
weirdness:
#endif
	/*
	 *  Build result in CAM ccb.
	 */
	sym_set_cam_result_error(np, cp, resid);

#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
finish:
#endif
	/*
	 *  Add this one to the COMP queue.
	 */
	sym_remque(&cp->link_ccbq);
	sym_insque_head(&cp->link_ccbq, &np->comp_ccbq);

	/*
	 *  Complete all those commands with either error 
	 *  or requeue condition.
	 */
	sym_flush_comp_queue(np, 0);

#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
	/*
	 *  Donnot start more than 1 command after an error.
	 */
	sym_start_next_ccbs(np, lp, 1);
#endif
}