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
typedef  long uint ;
struct viosrp_crq {int format; scalar_t__ status; } ;
struct scsi_info {int flags; long state; long resume_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  active_q; int /*<<< orphan*/  waiting_rsp; int /*<<< orphan*/  schedule_q; int /*<<< orphan*/  debit; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
#define  CONNECTED 143 
 scalar_t__ CRQ_ENTRY_OVERWRITTEN ; 
 long ERROR ; 
#define  ERR_DISCONNECT 142 
#define  ERR_DISCONNECTED 141 
#define  ERR_DISCONNECT_RECONNECT 140 
#define  MIGRATED 139 
#define  NO_QUEUE 138 
#define  PARTNER_DEREGISTER 137 
#define  PARTNER_FAILED 136 
#define  PREPARE_FOR_SUSPEND 135 
 int PREP_FOR_SUSPEND_ABORTED ; 
 int PREP_FOR_SUSPEND_OVERWRITE ; 
 int PREP_FOR_SUSPEND_PENDING ; 
 int RESPONSE_Q_DOWN ; 
#define  RESUME_FROM_SUSP 134 
 long SCHEDULE_DISCONNECT ; 
#define  SRP_PROCESSING 133 
 int TRANS_EVENT ; 
#define  UNCONFIGURING 132 
#define  UNDEFINED 131 
#define  WAIT_CONNECTION 130 
#define  WAIT_ENABLED 129 
#define  WAIT_IDLE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ibmvscsis_delete_client_info (struct scsi_info*,int) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int const,int) ; 
 int /*<<< orphan*/  ibmvscsis_ready_for_suspend (struct scsi_info*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ibmvscsis_trans_event(struct scsi_info *vscsi,
				  struct viosrp_crq *crq)
{
	long rc = ADAPT_SUCCESS;

	dev_dbg(&vscsi->dev, "trans_event: format %d, flags 0x%x, state 0x%hx\n",
		(int)crq->format, vscsi->flags, vscsi->state);

	switch (crq->format) {
	case MIGRATED:
	case PARTNER_FAILED:
	case PARTNER_DEREGISTER:
		ibmvscsis_delete_client_info(vscsi, true);
		if (crq->format == MIGRATED)
			vscsi->flags &= ~PREP_FOR_SUSPEND_OVERWRITE;
		switch (vscsi->state) {
		case NO_QUEUE:
		case ERR_DISCONNECTED:
		case UNDEFINED:
			break;

		case UNCONFIGURING:
			vscsi->flags |= (RESPONSE_Q_DOWN | TRANS_EVENT);
			break;

		case WAIT_ENABLED:
			break;

		case WAIT_CONNECTION:
			break;

		case CONNECTED:
			ibmvscsis_post_disconnect(vscsi, WAIT_IDLE,
						  (RESPONSE_Q_DOWN |
						   TRANS_EVENT));
			break;

		case SRP_PROCESSING:
			if ((vscsi->debit > 0) ||
			    !list_empty(&vscsi->schedule_q) ||
			    !list_empty(&vscsi->waiting_rsp) ||
			    !list_empty(&vscsi->active_q)) {
				dev_dbg(&vscsi->dev, "debit %d, sched %d, wait %d, active %d\n",
					vscsi->debit,
					(int)list_empty(&vscsi->schedule_q),
					(int)list_empty(&vscsi->waiting_rsp),
					(int)list_empty(&vscsi->active_q));
				dev_warn(&vscsi->dev, "connection lost with outstanding work\n");
			} else {
				dev_dbg(&vscsi->dev, "trans_event: SRP Processing, but no outstanding work\n");
			}

			ibmvscsis_post_disconnect(vscsi, WAIT_IDLE,
						  (RESPONSE_Q_DOWN |
						   TRANS_EVENT));
			break;

		case ERR_DISCONNECT:
		case ERR_DISCONNECT_RECONNECT:
		case WAIT_IDLE:
			vscsi->flags |= (RESPONSE_Q_DOWN | TRANS_EVENT);
			break;
		}
		break;

	case PREPARE_FOR_SUSPEND:
		dev_dbg(&vscsi->dev, "Prep for Suspend, crq status = 0x%x\n",
			(int)crq->status);
		switch (vscsi->state) {
		case ERR_DISCONNECTED:
		case WAIT_CONNECTION:
		case CONNECTED:
			ibmvscsis_ready_for_suspend(vscsi, false);
			break;
		case SRP_PROCESSING:
			vscsi->resume_state = vscsi->state;
			vscsi->flags |= PREP_FOR_SUSPEND_PENDING;
			if (crq->status == CRQ_ENTRY_OVERWRITTEN)
				vscsi->flags |= PREP_FOR_SUSPEND_OVERWRITE;
			ibmvscsis_post_disconnect(vscsi, WAIT_IDLE, 0);
			break;
		case NO_QUEUE:
		case UNDEFINED:
		case UNCONFIGURING:
		case WAIT_ENABLED:
		case ERR_DISCONNECT:
		case ERR_DISCONNECT_RECONNECT:
		case WAIT_IDLE:
			dev_err(&vscsi->dev, "Invalid state for Prepare for Suspend Trans Event: 0x%x\n",
				vscsi->state);
			break;
		}
		break;

	case RESUME_FROM_SUSP:
		dev_dbg(&vscsi->dev, "Resume from Suspend, crq status = 0x%x\n",
			(int)crq->status);
		if (vscsi->flags & PREP_FOR_SUSPEND_PENDING) {
			vscsi->flags |= PREP_FOR_SUSPEND_ABORTED;
		} else {
			if ((crq->status == CRQ_ENTRY_OVERWRITTEN) ||
			    (vscsi->flags & PREP_FOR_SUSPEND_OVERWRITE)) {
				ibmvscsis_post_disconnect(vscsi,
							  ERR_DISCONNECT_RECONNECT,
							  0);
				vscsi->flags &= ~PREP_FOR_SUSPEND_OVERWRITE;
			}
		}
		break;

	default:
		rc = ERROR;
		dev_err(&vscsi->dev, "trans_event: invalid format %d\n",
			(uint)crq->format);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT,
					  RESPONSE_Q_DOWN);
		break;
	}

	rc = vscsi->flags & SCHEDULE_DISCONNECT;

	dev_dbg(&vscsi->dev, "Leaving trans_event: flags 0x%x, state 0x%hx, rc %ld\n",
		vscsi->flags, vscsi->state, rc);

	return rc;
}