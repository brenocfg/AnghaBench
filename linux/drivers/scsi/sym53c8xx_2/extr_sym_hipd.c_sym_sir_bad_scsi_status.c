#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int u32 ;
struct sym_hcb {int squeue_ba; scalar_t__ last_cp; } ;
struct TYPE_13__ {void* start; } ;
struct TYPE_14__ {TYPE_5__ go; void* lastp; void* savep; } ;
struct TYPE_12__ {void* size; void* addr; } ;
struct TYPE_10__ {void* size; void* addr; } ;
struct TYPE_9__ {void* size; void* addr; } ;
struct TYPE_15__ {TYPE_6__ head; TYPE_4__ sense; TYPE_2__ cmd; TYPE_1__ smsg; } ;
struct sym_ccb {int ssss_status; int host_flags; int lun; int sv_scsi_status; int* sensecmd; int data_len; TYPE_7__ phys; int /*<<< orphan*/  extra_bytes; int /*<<< orphan*/  xerr_status; int /*<<< orphan*/  nego_status; int /*<<< orphan*/  host_status; int /*<<< orphan*/  host_xflags; void* goalp; void* startp; int /*<<< orphan*/  sns_bbuf; TYPE_8__* cmd; int /*<<< orphan*/ * scsi_smsg2; int /*<<< orphan*/  sv_resid; int /*<<< orphan*/  sv_xerr_status; int /*<<< orphan*/  target; } ;
struct TYPE_16__ {TYPE_3__* device; } ;
struct TYPE_11__ {int /*<<< orphan*/  scsi_level; } ;

/* Variables and functions */
 void* CCB_BA (struct sym_ccb*,int /*<<< orphan*/ ) ; 
 int HF_DATA_IN ; 
 int HF_SENSE ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_NEGOTIATE ; 
 int /*<<< orphan*/  IDENTIFY (int /*<<< orphan*/ ,int) ; 
 int INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int) ; 
 int REQUEST_SENSE ; 
 int SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_2 ; 
 int SYM_SNS_BBUF_LEN ; 
#define  S_BUSY 131 
#define  S_CHECK_COND 130 
 int S_ILLEGAL ; 
#define  S_QUEUE_FULL 129 
#define  S_TERMINATED 128 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nc_scratcha ; 
 int /*<<< orphan*/  scsi_smsg2 ; 
 int /*<<< orphan*/  sdata_in ; 
 int /*<<< orphan*/  select ; 
 int /*<<< orphan*/  sensecmd ; 
 int /*<<< orphan*/  sns_bbuf ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  sym_complete_error (struct sym_hcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_compute_residual (struct sym_hcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_dequeue_from_squeue (struct sym_hcb*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sym_flush_comp_queue (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int sym_prepare_nego (struct sym_hcb*,struct sym_ccb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_print_addr (TYPE_8__*,char*,char*) ; 
 int /*<<< orphan*/  sym_put_start_queue (struct sym_hcb*,struct sym_ccb*) ; 
 int sym_verbose ; 

__attribute__((used)) static void sym_sir_bad_scsi_status(struct sym_hcb *np, int num, struct sym_ccb *cp)
{
	u32		startp;
	u_char		s_status = cp->ssss_status;
	u_char		h_flags  = cp->host_flags;
	int		msglen;
	int		i;

	/*
	 *  Compute the index of the next job to start from SCRIPTS.
	 */
	i = (INL(np, nc_scratcha) - np->squeue_ba) / 4;

	/*
	 *  The last CCB queued used for IARB hint may be 
	 *  no longer relevant. Forget it.
	 */
#ifdef SYM_CONF_IARB_SUPPORT
	if (np->last_cp)
		np->last_cp = 0;
#endif

	/*
	 *  Now deal with the SCSI status.
	 */
	switch(s_status) {
	case S_BUSY:
	case S_QUEUE_FULL:
		if (sym_verbose >= 2) {
			sym_print_addr(cp->cmd, "%s\n",
			        s_status == S_BUSY ? "BUSY" : "QUEUE FULL\n");
		}
		/* fall through */
	default:	/* S_INT, S_INT_COND_MET, S_CONFLICT */
		sym_complete_error (np, cp);
		break;
	case S_TERMINATED:
	case S_CHECK_COND:
		/*
		 *  If we get an SCSI error when requesting sense, give up.
		 */
		if (h_flags & HF_SENSE) {
			sym_complete_error (np, cp);
			break;
		}

		/*
		 *  Dequeue all queued CCBs for that device not yet started,
		 *  and restart the SCRIPTS processor immediately.
		 */
		sym_dequeue_from_squeue(np, i, cp->target, cp->lun, -1);
		OUTL_DSP(np, SCRIPTA_BA(np, start));

 		/*
		 *  Save some info of the actual IO.
		 *  Compute the data residual.
		 */
		cp->sv_scsi_status = cp->ssss_status;
		cp->sv_xerr_status = cp->xerr_status;
		cp->sv_resid = sym_compute_residual(np, cp);

		/*
		 *  Prepare all needed data structures for 
		 *  requesting sense data.
		 */

		cp->scsi_smsg2[0] = IDENTIFY(0, cp->lun);
		msglen = 1;

		/*
		 *  If we are currently using anything different from 
		 *  async. 8 bit data transfers with that target,
		 *  start a negotiation, since the device may want 
		 *  to report us a UNIT ATTENTION condition due to 
		 *  a cause we currently ignore, and we donnot want 
		 *  to be stuck with WIDE and/or SYNC data transfer.
		 *
		 *  cp->nego_status is filled by sym_prepare_nego().
		 */
		cp->nego_status = 0;
		msglen += sym_prepare_nego(np, cp, &cp->scsi_smsg2[msglen]);
		/*
		 *  Message table indirect structure.
		 */
		cp->phys.smsg.addr	= CCB_BA(cp, scsi_smsg2);
		cp->phys.smsg.size	= cpu_to_scr(msglen);

		/*
		 *  sense command
		 */
		cp->phys.cmd.addr	= CCB_BA(cp, sensecmd);
		cp->phys.cmd.size	= cpu_to_scr(6);

		/*
		 *  patch requested size into sense command
		 */
		cp->sensecmd[0]		= REQUEST_SENSE;
		cp->sensecmd[1]		= 0;
		if (cp->cmd->device->scsi_level <= SCSI_2 && cp->lun <= 7)
			cp->sensecmd[1]	= cp->lun << 5;
		cp->sensecmd[4]		= SYM_SNS_BBUF_LEN;
		cp->data_len		= SYM_SNS_BBUF_LEN;

		/*
		 *  sense data
		 */
		memset(cp->sns_bbuf, 0, SYM_SNS_BBUF_LEN);
		cp->phys.sense.addr	= CCB_BA(cp, sns_bbuf);
		cp->phys.sense.size	= cpu_to_scr(SYM_SNS_BBUF_LEN);

		/*
		 *  requeue the command.
		 */
		startp = SCRIPTB_BA(np, sdata_in);

		cp->phys.head.savep	= cpu_to_scr(startp);
		cp->phys.head.lastp	= cpu_to_scr(startp);
		cp->startp		= cpu_to_scr(startp);
		cp->goalp		= cpu_to_scr(startp + 16);

		cp->host_xflags = 0;
		cp->host_status	= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
		cp->ssss_status = S_ILLEGAL;
		cp->host_flags	= (HF_SENSE|HF_DATA_IN);
		cp->xerr_status = 0;
		cp->extra_bytes = 0;

		cp->phys.head.go.start = cpu_to_scr(SCRIPTA_BA(np, select));

		/*
		 *  Requeue the command.
		 */
		sym_put_start_queue(np, cp);

		/*
		 *  Give back to upper layer everything we have dequeued.
		 */
		sym_flush_comp_queue(np, 0);
		break;
	}
}