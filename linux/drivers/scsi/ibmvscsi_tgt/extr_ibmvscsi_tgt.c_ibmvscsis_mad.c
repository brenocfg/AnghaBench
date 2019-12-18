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
struct viosrp_crq {int dummy; } ;
struct scsi_info {int state; long flags; int debit; int /*<<< orphan*/  dev; } ;
struct mad_common {int /*<<< orphan*/  status; int /*<<< orphan*/  type; } ;
struct iu_entry {int dummy; } ;
struct ibmvscsis_cmd {int /*<<< orphan*/  type; struct iu_entry* iue; } ;
struct TYPE_2__ {int /*<<< orphan*/  mad; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_MAD ; 
 long ADAPT_SUCCESS ; 
#define  CONNECTED 134 
 long ERROR ; 
#define  ERR_DISCONNECT 133 
#define  ERR_DISCONNECT_RECONNECT 132 
#define  SRP_PROCESSING 131 
#define  UNCONFIGURING 130 
#define  WAIT_CONNECTION 129 
#define  WAIT_IDLE 128 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 long be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,long,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 long ibmvscsis_copy_crq_packet (struct scsi_info*,struct ibmvscsis_cmd*,struct viosrp_crq*) ; 
 int /*<<< orphan*/  ibmvscsis_free_cmd_resources (struct scsi_info*,struct ibmvscsis_cmd*) ; 
 struct ibmvscsis_cmd* ibmvscsis_get_free_cmd (struct scsi_info*) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int const,int /*<<< orphan*/ ) ; 
 long ibmvscsis_process_mad (struct scsi_info*,struct iu_entry*) ; 
 int /*<<< orphan*/  ibmvscsis_send_mad_resp (struct scsi_info*,struct ibmvscsis_cmd*,struct viosrp_crq*) ; 
 TYPE_1__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static long ibmvscsis_mad(struct scsi_info *vscsi, struct viosrp_crq *crq)
{
	struct iu_entry *iue;
	struct ibmvscsis_cmd *cmd;
	struct mad_common *mad;
	long rc = ADAPT_SUCCESS;

	switch (vscsi->state) {
		/*
		 * We have not exchanged Init Msgs yet, so this MAD was sent
		 * before the last Transport Event; client will not be
		 * expecting a response.
		 */
	case WAIT_CONNECTION:
		dev_dbg(&vscsi->dev, "mad: in Wait Connection state, ignoring MAD, flags %d\n",
			vscsi->flags);
		return ADAPT_SUCCESS;

	case SRP_PROCESSING:
	case CONNECTED:
		break;

		/*
		 * We should never get here while we're in these states.
		 * Just log an error and get out.
		 */
	case UNCONFIGURING:
	case WAIT_IDLE:
	case ERR_DISCONNECT:
	case ERR_DISCONNECT_RECONNECT:
	default:
		dev_err(&vscsi->dev, "mad: invalid adapter state %d for mad\n",
			vscsi->state);
		return ADAPT_SUCCESS;
	}

	cmd = ibmvscsis_get_free_cmd(vscsi);
	if (!cmd) {
		dev_err(&vscsi->dev, "mad: failed to get cmd, debit %d\n",
			vscsi->debit);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		return ERROR;
	}
	iue = cmd->iue;
	cmd->type = ADAPTER_MAD;

	rc = ibmvscsis_copy_crq_packet(vscsi, cmd, crq);
	if (!rc) {
		mad = (struct mad_common *)&vio_iu(iue)->mad;

		dev_dbg(&vscsi->dev, "mad: type %d\n", be32_to_cpu(mad->type));

		rc = ibmvscsis_process_mad(vscsi, iue);

		dev_dbg(&vscsi->dev, "mad: status %hd, rc %ld\n",
			be16_to_cpu(mad->status), rc);

		if (!rc)
			ibmvscsis_send_mad_resp(vscsi, cmd, crq);
	} else {
		ibmvscsis_free_cmd_resources(vscsi, cmd);
	}

	dev_dbg(&vscsi->dev, "Leaving mad, rc %ld\n", rc);
	return rc;
}