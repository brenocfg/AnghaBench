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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct viosrp_crq {int /*<<< orphan*/  status; scalar_t__ format; int /*<<< orphan*/  valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_id; } ;
struct scsi_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; TYPE_1__ dds; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_FAILED ; 
 int /*<<< orphan*/  ERR_DISCONNECT ; 
 int /*<<< orphan*/  ERR_DISCONNECT_RECONNECT ; 
#define  H_CLOSED 131 
#define  H_DROPPED 130 
#define  H_REMOTE_PARM 129 
#define  H_SUCCESS 128 
 scalar_t__ MESSAGE_IN_CRQ ; 
 size_t MSG_HI ; 
 size_t MSG_LOW ; 
 int /*<<< orphan*/  PING_RESPONSE ; 
 int /*<<< orphan*/  RESPONSE_Q_DOWN ; 
 int /*<<< orphan*/  VALID_CMD_RESP_EL ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 long h_send_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ibmvscsis_ping_response(struct scsi_info *vscsi)
{
	struct viosrp_crq *crq;
	u64 buffer[2] = { 0, 0 };
	long rc;

	crq = (struct viosrp_crq *)&buffer;
	crq->valid = VALID_CMD_RESP_EL;
	crq->format = (u8)MESSAGE_IN_CRQ;
	crq->status = PING_RESPONSE;

	rc = h_send_crq(vscsi->dds.unit_id, cpu_to_be64(buffer[MSG_HI]),
			cpu_to_be64(buffer[MSG_LOW]));

	switch (rc) {
	case H_SUCCESS:
		break;
	case H_CLOSED:
		vscsi->flags |= CLIENT_FAILED;
		/* Fall through */
	case H_DROPPED:
		vscsi->flags |= RESPONSE_Q_DOWN;
		/* Fall through */
	case H_REMOTE_PARM:
		dev_err(&vscsi->dev, "ping_response: h_send_crq failed, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		break;
	default:
		dev_err(&vscsi->dev, "ping_response: h_send_crq returned unknown rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT, 0);
		break;
	}

	return rc;
}