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
struct TYPE_16__ {int /*<<< orphan*/  version; } ;
struct TYPE_15__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct TYPE_11__ {int* addr; void* ip_type; } ;
struct tcp_connect_and_offload_in_v1 {unsigned short cid; unsigned short defq_id; unsigned short hdr_ring_id; unsigned short data_ring_id; int do_offload; int tcp_window_size; int tcp_window_scale_count; TYPE_8__ hdr; TYPE_7__ dataout_template_pa; int /*<<< orphan*/  cq_id; void* tcp_port; TYPE_3__ ip_address; } ;
struct TYPE_12__ {int /*<<< orphan*/  u6_addr8; } ;
struct TYPE_13__ {TYPE_4__ in6_u; } ;
struct sockaddr_in6 {TYPE_5__ sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_10__ {int s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct phys_addr {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct hwi_controller {TYPE_1__* wrb_context; struct hwi_context_memory* phwi_ctxt; } ;
struct hwi_context_memory {TYPE_6__* be_cq; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {scalar_t__ nxt_cqid; scalar_t__ num_cpus; struct hwi_controller* phwi_ctrlr; struct be_ctrl_info ctrl; } ;
struct beiscsi_endpoint {unsigned short ep_cid; int dst_addr; int* dst6_addr; void* ip_type; void* dst_tcpport; } ;
struct be_sge {void* len; void* pa_lo; void* pa_hi; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {int size; int dma; struct tcp_connect_and_offload_in_v1* va; } ;
typedef  int __be32 ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {unsigned int ulp_num; } ;

/* Variables and functions */
 void* BEISCSI_IP_TYPE_V4 ; 
 void* BEISCSI_IP_TYPE_V6 ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 size_t BE_GET_CRI_FROM_CID (unsigned short) ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 scalar_t__ HWI_GET_DEF_BUFQ_ID (struct beiscsi_hba*,unsigned int) ; 
 scalar_t__ HWI_GET_DEF_HDRQ_ID (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  ISCSI_GET_PDU_TEMPLATE_ADDRESS (struct beiscsi_hba*,struct phys_addr*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MBX_CMD_VER1 ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_TCP_CONNECT_AND_OFFLOAD ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 struct be_mcc_wrb* alloc_mcc_wrb (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  is_chip_be2_be3r (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct tcp_connect_and_offload_in_v1*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_sge* nonembedded_sgl (struct be_mcc_wrb*) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

int mgmt_open_connection(struct beiscsi_hba *phba,
			 struct sockaddr *dst_addr,
			 struct beiscsi_endpoint *beiscsi_ep,
			 struct be_dma_mem *nonemb_cmd)
{
	struct hwi_controller *phwi_ctrlr;
	struct hwi_context_memory *phwi_context;
	struct sockaddr_in *daddr_in = (struct sockaddr_in *)dst_addr;
	struct sockaddr_in6 *daddr_in6 = (struct sockaddr_in6 *)dst_addr;
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	struct tcp_connect_and_offload_in_v1 *req;
	unsigned short def_hdr_id;
	unsigned short def_data_id;
	struct phys_addr template_address = { 0, 0 };
	struct phys_addr *ptemplate_address;
	unsigned int tag = 0;
	unsigned int i, ulp_num;
	unsigned short cid = beiscsi_ep->ep_cid;
	struct be_sge *sge;

	if (dst_addr->sa_family != PF_INET && dst_addr->sa_family != PF_INET6) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BG_%d : unknown addr family %d\n",
			    dst_addr->sa_family);
		return 0;
	}

	phwi_ctrlr = phba->phwi_ctrlr;
	phwi_context = phwi_ctrlr->phwi_ctxt;

	ulp_num = phwi_ctrlr->wrb_context[BE_GET_CRI_FROM_CID(cid)].ulp_num;

	def_hdr_id = (unsigned short)HWI_GET_DEF_HDRQ_ID(phba, ulp_num);
	def_data_id = (unsigned short)HWI_GET_DEF_BUFQ_ID(phba, ulp_num);

	ptemplate_address = &template_address;
	ISCSI_GET_PDU_TEMPLATE_ADDRESS(phba, ptemplate_address);
	if (mutex_lock_interruptible(&ctrl->mbox_lock))
		return 0;
	wrb = alloc_mcc_wrb(phba, &tag);
	if (!wrb) {
		mutex_unlock(&ctrl->mbox_lock);
		return 0;
	}

	sge = nonembedded_sgl(wrb);
	req = nonemb_cmd->va;
	memset(req, 0, sizeof(*req));

	be_wrb_hdr_prepare(wrb, nonemb_cmd->size, false, 1);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_TCP_CONNECT_AND_OFFLOAD,
			   nonemb_cmd->size);
	if (dst_addr->sa_family == PF_INET) {
		__be32 s_addr = daddr_in->sin_addr.s_addr;
		req->ip_address.ip_type = BEISCSI_IP_TYPE_V4;
		req->ip_address.addr[0] = s_addr & 0x000000ff;
		req->ip_address.addr[1] = (s_addr & 0x0000ff00) >> 8;
		req->ip_address.addr[2] = (s_addr & 0x00ff0000) >> 16;
		req->ip_address.addr[3] = (s_addr & 0xff000000) >> 24;
		req->tcp_port = ntohs(daddr_in->sin_port);
		beiscsi_ep->dst_addr = daddr_in->sin_addr.s_addr;
		beiscsi_ep->dst_tcpport = ntohs(daddr_in->sin_port);
		beiscsi_ep->ip_type = BEISCSI_IP_TYPE_V4;
	} else {
		/* else its PF_INET6 family */
		req->ip_address.ip_type = BEISCSI_IP_TYPE_V6;
		memcpy(&req->ip_address.addr,
		       &daddr_in6->sin6_addr.in6_u.u6_addr8, 16);
		req->tcp_port = ntohs(daddr_in6->sin6_port);
		beiscsi_ep->dst_tcpport = ntohs(daddr_in6->sin6_port);
		memcpy(&beiscsi_ep->dst6_addr,
		       &daddr_in6->sin6_addr.in6_u.u6_addr8, 16);
		beiscsi_ep->ip_type = BEISCSI_IP_TYPE_V6;
	}
	req->cid = cid;
	i = phba->nxt_cqid++;
	if (phba->nxt_cqid == phba->num_cpus)
		phba->nxt_cqid = 0;
	req->cq_id = phwi_context->be_cq[i].id;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BG_%d : i=%d cq_id=%d\n", i, req->cq_id);
	req->defq_id = def_hdr_id;
	req->hdr_ring_id = def_hdr_id;
	req->data_ring_id = def_data_id;
	req->do_offload = 1;
	req->dataout_template_pa.lo = ptemplate_address->lo;
	req->dataout_template_pa.hi = ptemplate_address->hi;
	sge->pa_hi = cpu_to_le32(upper_32_bits(nonemb_cmd->dma));
	sge->pa_lo = cpu_to_le32(nonemb_cmd->dma & 0xFFFFFFFF);
	sge->len = cpu_to_le32(nonemb_cmd->size);

	if (!is_chip_be2_be3r(phba)) {
		req->hdr.version = MBX_CMD_VER1;
		req->tcp_window_size = 0x8000;
		req->tcp_window_scale_count = 2;
	}

	be_mcc_notify(phba, tag);
	mutex_unlock(&ctrl->mbox_lock);
	return tag;
}