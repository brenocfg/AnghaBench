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
typedef  int uint ;
struct TYPE_9__ {int /*<<< orphan*/  length; void* status; } ;
struct viosrp_adapter_info {int /*<<< orphan*/  buffer; TYPE_2__ common; } ;
struct TYPE_12__ {TYPE_4__* window; int /*<<< orphan*/  partition_num; int /*<<< orphan*/  partition_name; } ;
struct TYPE_10__ {void* os_type; void* mad_version; int /*<<< orphan*/  partition_name; int /*<<< orphan*/  srp_version; void* partition_number; } ;
struct scsi_info {int /*<<< orphan*/  dev; TYPE_6__* dma_dev; TYPE_5__ dds; TYPE_3__ client_data; int /*<<< orphan*/  flags; } ;
struct mad_adapter_info_data {void** port_max_txu; void* os_type; void* mad_version; void* partition_number; int /*<<< orphan*/  partition_name; int /*<<< orphan*/  srp_version; } ;
struct iu_entry {long target; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {struct viosrp_adapter_info adapter_info; } ;
struct TYPE_14__ {TYPE_1__ mad; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  liobn; } ;

/* Variables and functions */
 int CLIENT_FAILED ; 
 int /*<<< orphan*/  ERR_DISCONNECT_RECONNECT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  H_DEST_PARM 131 
#define  H_PERMISSION 130 
#define  H_SOURCE_PARM 129 
#define  H_SUCCESS 128 
 int /*<<< orphan*/  LINUX ; 
 size_t LOCAL ; 
 int /*<<< orphan*/  MAD_VERSION_1 ; 
 int /*<<< orphan*/  MAX_TXU ; 
 size_t REMOTE ; 
 int RESPONSE_Q_DOWN ; 
 int /*<<< orphan*/  SRP_VERSION ; 
 int /*<<< orphan*/  VIOSRP_MAD_FAILED ; 
 int /*<<< orphan*/  VIOSRP_MAD_SUCCESS ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (void*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ connection_broken (struct scsi_info*) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,long,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,long) ; 
 struct mad_adapter_info_data* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct mad_adapter_info_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 long h_copy_rdma (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvscsis_post_disconnect (struct scsi_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static long ibmvscsis_adapter_info(struct scsi_info *vscsi,
				   struct iu_entry *iue)
{
	struct viosrp_adapter_info *mad = &vio_iu(iue)->mad.adapter_info;
	struct mad_adapter_info_data *info;
	uint flag_bits = 0;
	dma_addr_t token;
	long rc;

	mad->common.status = cpu_to_be16(VIOSRP_MAD_SUCCESS);

	if (be16_to_cpu(mad->common.length) > sizeof(*info)) {
		mad->common.status = cpu_to_be16(VIOSRP_MAD_FAILED);
		return 0;
	}

	info = dma_alloc_coherent(&vscsi->dma_dev->dev, sizeof(*info), &token,
				  GFP_ATOMIC);
	if (!info) {
		dev_err(&vscsi->dev, "bad dma_alloc_coherent %p\n",
			iue->target);
		mad->common.status = cpu_to_be16(VIOSRP_MAD_FAILED);
		return 0;
	}

	/* Get remote info */
	rc = h_copy_rdma(be16_to_cpu(mad->common.length),
			 vscsi->dds.window[REMOTE].liobn,
			 be64_to_cpu(mad->buffer),
			 vscsi->dds.window[LOCAL].liobn, token);

	if (rc != H_SUCCESS) {
		if (rc == H_PERMISSION) {
			if (connection_broken(vscsi))
				flag_bits = (RESPONSE_Q_DOWN | CLIENT_FAILED);
		}
		dev_warn(&vscsi->dev, "adapter_info: h_copy_rdma from client failed, rc %ld\n",
			 rc);
		dev_dbg(&vscsi->dev, "adapter_info: ioba 0x%llx, flags 0x%x, flag_bits 0x%x\n",
			be64_to_cpu(mad->buffer), vscsi->flags, flag_bits);
		ibmvscsis_post_disconnect(vscsi, ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		goto free_dma;
	}

	/*
	 * Copy client info, but ignore partition number, which we
	 * already got from phyp - unless we failed to get it from
	 * phyp (e.g. if we're running on a p5 system).
	 */
	if (vscsi->client_data.partition_number == 0)
		vscsi->client_data.partition_number =
			be32_to_cpu(info->partition_number);
	strncpy(vscsi->client_data.srp_version, info->srp_version,
		sizeof(vscsi->client_data.srp_version));
	strncpy(vscsi->client_data.partition_name, info->partition_name,
		sizeof(vscsi->client_data.partition_name));
	vscsi->client_data.mad_version = be32_to_cpu(info->mad_version);
	vscsi->client_data.os_type = be32_to_cpu(info->os_type);

	/* Copy our info */
	strncpy(info->srp_version, SRP_VERSION,
		sizeof(info->srp_version));
	strncpy(info->partition_name, vscsi->dds.partition_name,
		sizeof(info->partition_name));
	info->partition_number = cpu_to_be32(vscsi->dds.partition_num);
	info->mad_version = cpu_to_be32(MAD_VERSION_1);
	info->os_type = cpu_to_be32(LINUX);
	memset(&info->port_max_txu[0], 0, sizeof(info->port_max_txu));
	info->port_max_txu[0] = cpu_to_be32(MAX_TXU);

	dma_wmb();
	rc = h_copy_rdma(sizeof(*info), vscsi->dds.window[LOCAL].liobn,
			 token, vscsi->dds.window[REMOTE].liobn,
			 be64_to_cpu(mad->buffer));
	switch (rc) {
	case H_SUCCESS:
		break;

	case H_SOURCE_PARM:
	case H_DEST_PARM:
	case H_PERMISSION:
		if (connection_broken(vscsi))
			flag_bits = (RESPONSE_Q_DOWN | CLIENT_FAILED);
		/* Fall through */
	default:
		dev_err(&vscsi->dev, "adapter_info: h_copy_rdma to client failed, rc %ld\n",
			rc);
		ibmvscsis_post_disconnect(vscsi,
					  ERR_DISCONNECT_RECONNECT,
					  flag_bits);
		break;
	}

free_dma:
	dma_free_coherent(&vscsi->dma_dev->dev, sizeof(*info), info, token);
	dev_dbg(&vscsi->dev, "Leaving adapter_info, rc %ld\n", rc);

	return rc;
}