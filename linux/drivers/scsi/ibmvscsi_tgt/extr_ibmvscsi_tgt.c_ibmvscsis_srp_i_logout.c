#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct viosrp_crq {int dummy; } ;
struct srp_i_logout {int /*<<< orphan*/  tag; } ;
struct scsi_info {scalar_t__ debit; int /*<<< orphan*/  waiting_rsp; int /*<<< orphan*/  dev; int /*<<< orphan*/  schedule_q; } ;
struct mad_common {int dummy; } ;
struct iu_entry {int dummy; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  tag; int /*<<< orphan*/  format; } ;
struct ibmvscsis_cmd {int /*<<< orphan*/  list; TYPE_2__ rsp; struct iu_entry* iue; } ;
struct TYPE_4__ {struct srp_i_logout i_logout; } ;
struct TYPE_6__ {TYPE_1__ srp; } ;

/* Variables and functions */
 long ADAPT_SUCCESS ; 
 int /*<<< orphan*/  ERR_DISCONNECT ; 
 int /*<<< orphan*/  SRP_FORMAT ; 
 int /*<<< orphan*/  WAIT_IDLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_send_messages (struct scsi_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 TYPE_3__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static long ibmvscsis_srp_i_logout(struct scsi_info *vscsi,
				   struct ibmvscsis_cmd *cmd,
				   struct viosrp_crq *crq)
{
	struct iu_entry *iue = cmd->iue;
	struct srp_i_logout *log_out = &vio_iu(iue)->srp.i_logout;
	long rc = ADAPT_SUCCESS;

	if ((vscsi->debit > 0) || !list_empty(&vscsi->schedule_q) ||
	    !list_empty(&vscsi->waiting_rsp)) {
		dev_err(&vscsi->dev, "i_logout: outstanding work\n");
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
	} else {
		cmd->rsp.format = SRP_FORMAT;
		cmd->rsp.tag = log_out->tag;
		cmd->rsp.len = sizeof(struct mad_common);
		list_add_tail(&cmd->list, &vscsi->waiting_rsp);
		ibmvscsis_send_messages(vscsi);

		ibmvscsis_post_disconnect(vscsi, WAIT_IDLE, 0);
	}

	return rc;
}