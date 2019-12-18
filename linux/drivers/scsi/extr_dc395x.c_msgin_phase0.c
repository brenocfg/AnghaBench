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
typedef  int /*<<< orphan*/  u16 ;
struct ScsiReqBlk {int* msgin_buf; int state; int msg_count; int /*<<< orphan*/ * msgout_buf; int /*<<< orphan*/  cmd; int /*<<< orphan*/  total_xfer_length; } ;
struct DeviceCtlBlk {int /*<<< orphan*/  identify_msg; int /*<<< orphan*/  flag; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct AdapterCtlBlk {scalar_t__ msg_len; struct DeviceCtlBlk* active_dcb; } ;

/* Variables and functions */
#define  ABORT 138 
 int /*<<< orphan*/  ABORT_DEV_ ; 
#define  COMMAND_COMPLETE 137 
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395x_ENABLE_MSGOUT ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DISCONNECT 136 
 int DO_CLRATN ; 
 int DO_DATALATCH ; 
#define  EXTENDED_MESSAGE 135 
 int EXTENDED_SDTR ; 
 int EXTENDED_WDTR ; 
#define  HEAD_OF_QUEUE_TAG 134 
 int IDENTIFY_BASE ; 
#define  MESSAGE_REJECT 133 
#define  MSG_IGNOREWIDE 132 
#define  ORDERED_QUEUE_TAG 131 
 int /*<<< orphan*/  PH_BUS_FREE ; 
#define  RESTORE_POINTERS 130 
#define  SAVE_POINTERS 129 
 int /*<<< orphan*/  SCMD_MSGACCEPT ; 
#define  SIMPLE_QUEUE_TAG 128 
 int SRB_DISCONNECT ; 
 int SRB_DO_SYNC_NEGO ; 
 int SRB_DO_WIDE_NEGO ; 
 int SRB_MSGIN ; 
 int SRB_MSGOUT ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_FIFO ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  enable_msgout_abort (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 scalar_t__ msgin_completed (int*,scalar_t__) ; 
 struct ScsiReqBlk* msgin_qtag (struct AdapterCtlBlk*,struct DeviceCtlBlk*,int) ; 
 int /*<<< orphan*/  msgin_reject (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  msgin_set_async (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  msgin_set_nowide (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  msgin_set_sync (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  msgin_set_wide (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 

__attribute__((used)) static void msgin_phase0(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	struct DeviceCtlBlk *dcb = acb->active_dcb;
	dprintkdbg(DBG_0, "msgin_phase0: (0x%p)\n", srb->cmd);

	srb->msgin_buf[acb->msg_len++] = DC395x_read8(acb, TRM_S1040_SCSI_FIFO);
	if (msgin_completed(srb->msgin_buf, acb->msg_len)) {
		/* Now eval the msg */
		switch (srb->msgin_buf[0]) {
		case DISCONNECT:
			srb->state = SRB_DISCONNECT;
			break;

		case SIMPLE_QUEUE_TAG:
		case HEAD_OF_QUEUE_TAG:
		case ORDERED_QUEUE_TAG:
			srb =
			    msgin_qtag(acb, dcb,
					      srb->msgin_buf[1]);
			break;

		case MESSAGE_REJECT:
			DC395x_write16(acb, TRM_S1040_SCSI_CONTROL,
				       DO_CLRATN | DO_DATALATCH);
			/* A sync nego message was rejected ! */
			if (srb->state & SRB_DO_SYNC_NEGO) {
				msgin_set_async(acb, srb);
				break;
			}
			/* A wide nego message was rejected ! */
			if (srb->state & SRB_DO_WIDE_NEGO) {
				msgin_set_nowide(acb, srb);
				break;
			}
			enable_msgout_abort(acb, srb);
			/*srb->state |= SRB_ABORT_SENT */
			break;

		case EXTENDED_MESSAGE:
			/* SDTR */
			if (srb->msgin_buf[1] == 3
			    && srb->msgin_buf[2] == EXTENDED_SDTR) {
				msgin_set_sync(acb, srb);
				break;
			}
			/* WDTR */
			if (srb->msgin_buf[1] == 2
			    && srb->msgin_buf[2] == EXTENDED_WDTR
			    && srb->msgin_buf[3] <= 2) { /* sanity check ... */
				msgin_set_wide(acb, srb);
				break;
			}
			msgin_reject(acb, srb);
			break;

		case MSG_IGNOREWIDE:
			/* Discard  wide residual */
			dprintkdbg(DBG_0, "msgin_phase0: Ignore Wide Residual!\n");
			break;

		case COMMAND_COMPLETE:
			/* nothing has to be done */
			break;

		case SAVE_POINTERS:
			/*
			 * SAVE POINTER may be ignored as we have the struct
			 * ScsiReqBlk* associated with the scsi command.
			 */
			dprintkdbg(DBG_0, "msgin_phase0: (0x%p) "
				"SAVE POINTER rem=%i Ignore\n",
				srb->cmd, srb->total_xfer_length);
			break;

		case RESTORE_POINTERS:
			dprintkdbg(DBG_0, "msgin_phase0: RESTORE POINTER. Ignore\n");
			break;

		case ABORT:
			dprintkdbg(DBG_0, "msgin_phase0: (0x%p) "
				"<%02i-%i> ABORT msg\n",
				srb->cmd, dcb->target_id,
				dcb->target_lun);
			dcb->flag |= ABORT_DEV_;
			enable_msgout_abort(acb, srb);
			break;

		default:
			/* reject unknown messages */
			if (srb->msgin_buf[0] & IDENTIFY_BASE) {
				dprintkdbg(DBG_0, "msgin_phase0: Identify msg\n");
				srb->msg_count = 1;
				srb->msgout_buf[0] = dcb->identify_msg;
				DC395x_ENABLE_MSGOUT;
				srb->state |= SRB_MSGOUT;
				/*break; */
			}
			msgin_reject(acb, srb);
		}

		/* Clear counter and MsgIn state */
		srb->state &= ~SRB_MSGIN;
		acb->msg_len = 0;
	}
	*pscsi_status = PH_BUS_FREE;
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important ... you know! */
	DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, SCMD_MSGACCEPT);
}