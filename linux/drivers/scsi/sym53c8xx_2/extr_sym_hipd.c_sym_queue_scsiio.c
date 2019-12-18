#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_12__ {int /*<<< orphan*/  uval; int /*<<< orphan*/  sval; int /*<<< orphan*/  wval; } ;
struct TYPE_8__ {scalar_t__ check_nego; } ;
struct sym_tcb {TYPE_5__ head; int /*<<< orphan*/  nego_cp; TYPE_1__ tgoal; } ;
struct sym_lcb {int curr_flags; int tags_since; int tags_si; scalar_t__* tags_sum; } ;
struct sym_hcb {struct sym_tcb* target; } ;
struct TYPE_13__ {void* size; int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {size_t sel_id; int /*<<< orphan*/  sel_scntl4; int /*<<< orphan*/  sel_sxfer; int /*<<< orphan*/  sel_scntl3; } ;
struct TYPE_9__ {void* restart; void* start; } ;
struct TYPE_10__ {TYPE_2__ go; } ;
struct TYPE_14__ {TYPE_6__ smsg; TYPE_4__ select; TYPE_3__ head; } ;
struct sym_ccb {size_t target; int tag; int* scsi_smsg; int order; int ext_sg; scalar_t__ ext_ofs; scalar_t__ extra_bytes; scalar_t__ host_flags; scalar_t__ xerr_status; int /*<<< orphan*/  ssss_status; scalar_t__ nego_status; int /*<<< orphan*/  host_status; scalar_t__ host_xflags; TYPE_7__ phys; struct scsi_cmnd* cmd; } ;
struct scsi_device {int /*<<< orphan*/  lun; } ;
struct scsi_cmnd {scalar_t__* cmnd; struct scsi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCB_BA (struct sym_ccb*,int /*<<< orphan*/ ) ; 
 int DEBUG_FLAGS ; 
 int DEBUG_TAGS ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_NEGOTIATE ; 
 int IDENTIFY (int,int /*<<< orphan*/ ) ; 
 scalar_t__ INQUIRY ; 
#define  M_HEAD_TAG 129 
#define  M_ORDERED_TAG 128 
 int M_SIMPLE_TAG ; 
 int NO_TAG ; 
 scalar_t__ REQUEST_SENSE ; 
 int SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int SYM_CONF_MAX_TAG ; 
 int SYM_DISC_ENABLED ; 
 int /*<<< orphan*/  S_ILLEGAL ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  resel_dsa ; 
 int /*<<< orphan*/  scsi_smsg ; 
 int /*<<< orphan*/  select ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,int /*<<< orphan*/ ) ; 
 int sym_prepare_nego (struct sym_hcb*,struct sym_ccb*,int*) ; 
 int /*<<< orphan*/  sym_print_addr (struct scsi_cmnd*,char*) ; 
 int sym_setup_data_and_start (struct sym_hcb*,struct scsi_cmnd*,struct sym_ccb*) ; 
 int sym_verbose ; 

int sym_queue_scsiio(struct sym_hcb *np, struct scsi_cmnd *cmd, struct sym_ccb *cp)
{
	struct scsi_device *sdev = cmd->device;
	struct sym_tcb *tp;
	struct sym_lcb *lp;
	u_char	*msgptr;
	u_int   msglen;
	int can_disconnect;

	/*
	 *  Keep track of the IO in our CCB.
	 */
	cp->cmd = cmd;

	/*
	 *  Retrieve the target descriptor.
	 */
	tp = &np->target[cp->target];

	/*
	 *  Retrieve the lun descriptor.
	 */
	lp = sym_lp(tp, sdev->lun);

	can_disconnect = (cp->tag != NO_TAG) ||
		(lp && (lp->curr_flags & SYM_DISC_ENABLED));

	msgptr = cp->scsi_smsg;
	msglen = 0;
	msgptr[msglen++] = IDENTIFY(can_disconnect, sdev->lun);

	/*
	 *  Build the tag message if present.
	 */
	if (cp->tag != NO_TAG) {
		u_char order = cp->order;

		switch(order) {
		case M_ORDERED_TAG:
			break;
		case M_HEAD_TAG:
			break;
		default:
			order = M_SIMPLE_TAG;
		}
#ifdef SYM_OPT_LIMIT_COMMAND_REORDERING
		/*
		 *  Avoid too much reordering of SCSI commands.
		 *  The algorithm tries to prevent completion of any 
		 *  tagged command from being delayed against more 
		 *  than 3 times the max number of queued commands.
		 */
		if (lp && lp->tags_since > 3*SYM_CONF_MAX_TAG) {
			lp->tags_si = !(lp->tags_si);
			if (lp->tags_sum[lp->tags_si]) {
				order = M_ORDERED_TAG;
				if ((DEBUG_FLAGS & DEBUG_TAGS)||sym_verbose>1) {
					sym_print_addr(cmd,
						"ordered tag forced.\n");
				}
			}
			lp->tags_since = 0;
		}
#endif
		msgptr[msglen++] = order;

		/*
		 *  For less than 128 tags, actual tags are numbered 
		 *  1,3,5,..2*MAXTAGS+1,since we may have to deal 
		 *  with devices that have problems with #TAG 0 or too 
		 *  great #TAG numbers. For more tags (up to 256), 
		 *  we use directly our tag number.
		 */
#if SYM_CONF_MAX_TASK > (512/4)
		msgptr[msglen++] = cp->tag;
#else
		msgptr[msglen++] = (cp->tag << 1) + 1;
#endif
	}

	/*
	 *  Build a negotiation message if needed.
	 *  (nego_status is filled by sym_prepare_nego())
	 *
	 *  Always negotiate on INQUIRY and REQUEST SENSE.
	 *
	 */
	cp->nego_status = 0;
	if ((tp->tgoal.check_nego ||
	     cmd->cmnd[0] == INQUIRY || cmd->cmnd[0] == REQUEST_SENSE) &&
	    !tp->nego_cp && lp) {
		msglen += sym_prepare_nego(np, cp, msgptr + msglen);
	}

	/*
	 *  Startqueue
	 */
	cp->phys.head.go.start   = cpu_to_scr(SCRIPTA_BA(np, select));
	cp->phys.head.go.restart = cpu_to_scr(SCRIPTA_BA(np, resel_dsa));

	/*
	 *  select
	 */
	cp->phys.select.sel_id		= cp->target;
	cp->phys.select.sel_scntl3	= tp->head.wval;
	cp->phys.select.sel_sxfer	= tp->head.sval;
	cp->phys.select.sel_scntl4	= tp->head.uval;

	/*
	 *  message
	 */
	cp->phys.smsg.addr	= CCB_BA(cp, scsi_smsg);
	cp->phys.smsg.size	= cpu_to_scr(msglen);

	/*
	 *  status
	 */
	cp->host_xflags		= 0;
	cp->host_status		= cp->nego_status ? HS_NEGOTIATE : HS_BUSY;
	cp->ssss_status		= S_ILLEGAL;
	cp->xerr_status		= 0;
	cp->host_flags		= 0;
	cp->extra_bytes		= 0;

	/*
	 *  extreme data pointer.
	 *  shall be positive, so -1 is lower than lowest.:)
	 */
	cp->ext_sg  = -1;
	cp->ext_ofs = 0;

	/*
	 *  Build the CDB and DATA descriptor block 
	 *  and start the IO.
	 */
	return sym_setup_data_and_start(np, cmd, cp);
}