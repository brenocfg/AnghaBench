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
typedef  scalar_t__ u16 ;
struct viosrp_crq {int /*<<< orphan*/  IU_data_ptr; int /*<<< orphan*/  IU_length; } ;
struct TYPE_5__ {TYPE_1__* window; } ;
struct scsi_info {int /*<<< orphan*/  dev; TYPE_2__ dds; } ;
struct iu_entry {scalar_t__ iu_len; int /*<<< orphan*/  remote_token; TYPE_3__* sbuf; } ;
struct ibmvscsis_cmd {int /*<<< orphan*/  init_time; struct iu_entry* iue; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  liobn; } ;

/* Variables and functions */
 int CLIENT_FAILED ; 
 int /*<<< orphan*/  ERR_DISCONNECT_RECONNECT ; 
#define  H_DEST_PARM 131 
#define  H_PERMISSION 130 
#define  H_SOURCE_PARM 129 
#define  H_SUCCESS 128 
 size_t LOCAL ; 
 size_t REMOTE ; 
 int RESPONSE_Q_DOWN ; 
 scalar_t__ SRP_MAX_IU_LEN ; 
 long SRP_VIOLATION ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_broken (struct scsi_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 long h_copy_rdma (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mftb () ; 

__attribute__((used)) static long ibmvscsis_copy_crq_packet(struct scsi_info *vscsi,
				      struct ibmvscsis_cmd *cmd,
				      struct viosrp_crq *crq)
{
	struct iu_entry *iue = cmd->iue;
	long rc = 0;
	u16 len;

	len = be16_to_cpu(crq->IU_length);
	if ((len > SRP_MAX_IU_LEN) || (len == 0)) {
		dev_err(&vscsi->dev, "copy_crq: Invalid len %d passed", len);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		return SRP_VIOLATION;
	}

	rc = h_copy_rdma(len, vscsi->dds.window[REMOTE].liobn,
			 be64_to_cpu(crq->IU_data_ptr),
			 vscsi->dds.window[LOCAL].liobn, iue->sbuf->dma);

	switch (rc) {
	case H_SUCCESS:
		cmd->init_time = mftb();
		iue->remote_token = crq->IU_data_ptr;
		iue->iu_len = len;
		dev_dbg(&vscsi->dev, "copy_crq: ioba 0x%llx, init_time 0x%llx\n",
			be64_to_cpu(crq->IU_data_ptr), cmd->init_time);
		break;
	case H_PERMISSION:
		if (connection_broken(vscsi))
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT,
						  (RESPONSE_Q_DOWN |
						   CLIENT_FAILED));
		else
			ibmvscsis_post_disconnect(vscsi,
						  ERR_DISCONNECT_RECONNECT, 0);

		dev_err(&vscsi->dev, "copy_crq: h_copy_rdma failed, rc %ld\n",
			rc);
		break;
	case H_DEST_PARM:
	case H_SOURCE_PARM:
	default:
		dev_err(&vscsi->dev, "copy_crq: h_copy_rdma failed, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT, 0);
		break;
	}

	return rc;
}