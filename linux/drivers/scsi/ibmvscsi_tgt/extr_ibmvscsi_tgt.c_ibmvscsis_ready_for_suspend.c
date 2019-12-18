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
struct viosrp_crq {scalar_t__ valid; scalar_t__ format; } ;
struct TYPE_4__ {int /*<<< orphan*/  unit_id; } ;
struct TYPE_3__ {int index; struct viosrp_crq* base_addr; } ;
struct scsi_info {int flags; scalar_t__ state; int /*<<< orphan*/  dev; TYPE_2__ dds; TYPE_1__ cmd_q; } ;

/* Variables and functions */
 scalar_t__ CONNECTED ; 
 scalar_t__ ERR_DISCONNECT_RECONNECT ; 
 int /*<<< orphan*/  H_READY_FOR_SUSPEND ; 
 int PREP_FOR_SUSPEND_ABORTED ; 
 int PREP_FOR_SUSPEND_OVERWRITE ; 
 int PREP_FOR_SUSPEND_PENDING ; 
 scalar_t__ RESUME_FROM_SUSP ; 
 scalar_t__ VALID_TRANS_EVENT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 long h_vioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_reset_queue (struct scsi_info*) ; 

__attribute__((used)) static long ibmvscsis_ready_for_suspend(struct scsi_info *vscsi, bool idle)
{
	long rc = 0;
	struct viosrp_crq *crq;

	/* See if there is a Resume event in the queue */
	crq = vscsi->cmd_q.base_addr + vscsi->cmd_q.index;

	dev_dbg(&vscsi->dev, "ready_suspend: flags 0x%x, state 0x%hx crq_valid:%x\n",
		vscsi->flags, vscsi->state, (int)crq->valid);

	if (!(vscsi->flags & PREP_FOR_SUSPEND_ABORTED) && !(crq->valid)) {
		rc = h_vioctl(vscsi->dds.unit_id, H_READY_FOR_SUSPEND, 0, 0, 0,
			      0, 0);
		if (rc) {
			dev_err(&vscsi->dev, "Ready for Suspend Vioctl failed: %ld\n",
				rc);
			rc = 0;
		}
	} else if (((vscsi->flags & PREP_FOR_SUSPEND_OVERWRITE) &&
		    (vscsi->flags & PREP_FOR_SUSPEND_ABORTED)) ||
		   ((crq->valid) && ((crq->valid != VALID_TRANS_EVENT) ||
				     (crq->format != RESUME_FROM_SUSP)))) {
		if (idle) {
			vscsi->state = ERR_DISCONNECT_RECONNECT;
			ibmvscsis_reset_queue(vscsi);
			rc = -1;
		} else if (vscsi->state == CONNECTED) {
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);
		}

		vscsi->flags &= ~PREP_FOR_SUSPEND_OVERWRITE;

		if ((crq->valid) && ((crq->valid != VALID_TRANS_EVENT) ||
				     (crq->format != RESUME_FROM_SUSP)))
			dev_err(&vscsi->dev, "Invalid element in CRQ after Prepare for Suspend");
	}

	vscsi->flags &= ~(PREP_FOR_SUSPEND_PENDING | PREP_FOR_SUSPEND_ABORTED);

	return rc;
}