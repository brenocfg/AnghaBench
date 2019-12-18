#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct nvme_fc_port_info {void* port_name; void* node_name; int /*<<< orphan*/  port_role; } ;
struct nvme_fc_local_port {scalar_t__ private; int /*<<< orphan*/  port_num; } ;
struct TYPE_11__ {int /*<<< orphan*/  wwn; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  wwn; } ;
struct TYPE_10__ {TYPE_1__ u; } ;
struct lpfc_vport {int nvmei_support; struct nvme_fc_local_port* localport; struct lpfc_hba* phba; TYPE_4__ fc_portname; TYPE_2__ fc_nodename; } ;
struct lpfc_nvme_lport {int /*<<< orphan*/  fc4NvmeLsCmpls; int /*<<< orphan*/  fc4NvmeLsRequests; int /*<<< orphan*/  cmpl_ls_err; int /*<<< orphan*/  cmpl_ls_xb; int /*<<< orphan*/  cmpl_fcp_err; int /*<<< orphan*/  cmpl_fcp_xb; int /*<<< orphan*/  xmt_ls_err; int /*<<< orphan*/  xmt_ls_abort; int /*<<< orphan*/  xmt_fcp_abort; int /*<<< orphan*/  xmt_fcp_wqerr; int /*<<< orphan*/  xmt_fcp_err; int /*<<< orphan*/  xmt_fcp_qdepth; int /*<<< orphan*/  xmt_fcp_bad_ndlp; int /*<<< orphan*/  xmt_fcp_noxri; struct lpfc_vport* vport; } ;
struct TYPE_13__ {int /*<<< orphan*/  num_present_cpu; } ;
struct lpfc_hba {scalar_t__ cfg_fcp_io_sched; TYPE_6__* pcidev; TYPE_5__ sli4_hba; int /*<<< orphan*/  cfg_hdw_queue; scalar_t__ cfg_nvme_seg_cnt; } ;
struct TYPE_15__ {scalar_t__ max_sgl_segments; int /*<<< orphan*/  max_hw_queues; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NVME_FC ; 
 int /*<<< orphan*/  FC_PORT_ROLE_NVME_INITIATOR ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_NVME ; 
 int LOG_NVME_DISC ; 
 scalar_t__ LPFC_FCP_SCHED_BY_HDWQ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__ lpfc_nvme_template ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,struct nvme_fc_local_port*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct nvme_fc_port_info*,int /*<<< orphan*/ ,int) ; 
 int nvme_fc_register_localport (struct nvme_fc_port_info*,TYPE_7__*,int /*<<< orphan*/ *,struct nvme_fc_local_port**) ; 
 void* wwn_to_u64 (int /*<<< orphan*/ ) ; 

int
lpfc_nvme_create_localport(struct lpfc_vport *vport)
{
	int ret = 0;
	struct lpfc_hba  *phba = vport->phba;
	struct nvme_fc_port_info nfcp_info;
	struct nvme_fc_local_port *localport;
	struct lpfc_nvme_lport *lport;

	/* Initialize this localport instance.  The vport wwn usage ensures
	 * that NPIV is accounted for.
	 */
	memset(&nfcp_info, 0, sizeof(struct nvme_fc_port_info));
	nfcp_info.port_role = FC_PORT_ROLE_NVME_INITIATOR;
	nfcp_info.node_name = wwn_to_u64(vport->fc_nodename.u.wwn);
	nfcp_info.port_name = wwn_to_u64(vport->fc_portname.u.wwn);

	/* We need to tell the transport layer + 1 because it takes page
	 * alignment into account. When space for the SGL is allocated we
	 * allocate + 3, one for cmd, one for rsp and one for this alignment
	 */
	lpfc_nvme_template.max_sgl_segments = phba->cfg_nvme_seg_cnt + 1;

	/* Advertise how many hw queues we support based on fcp_io_sched */
	if (phba->cfg_fcp_io_sched == LPFC_FCP_SCHED_BY_HDWQ)
		lpfc_nvme_template.max_hw_queues = phba->cfg_hdw_queue;
	else
		lpfc_nvme_template.max_hw_queues =
			phba->sli4_hba.num_present_cpu;

	if (!IS_ENABLED(CONFIG_NVME_FC))
		return ret;

	/* localport is allocated from the stack, but the registration
	 * call allocates heap memory as well as the private area.
	 */

	ret = nvme_fc_register_localport(&nfcp_info, &lpfc_nvme_template,
					 &vport->phba->pcidev->dev, &localport);
	if (!ret) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME | LOG_NVME_DISC,
				 "6005 Successfully registered local "
				 "NVME port num %d, localP x%px, private "
				 "x%px, sg_seg %d\n",
				 localport->port_num, localport,
				 localport->private,
				 lpfc_nvme_template.max_sgl_segments);

		/* Private is our lport size declared in the template. */
		lport = (struct lpfc_nvme_lport *)localport->private;
		vport->localport = localport;
		lport->vport = vport;
		vport->nvmei_support = 1;

		atomic_set(&lport->xmt_fcp_noxri, 0);
		atomic_set(&lport->xmt_fcp_bad_ndlp, 0);
		atomic_set(&lport->xmt_fcp_qdepth, 0);
		atomic_set(&lport->xmt_fcp_err, 0);
		atomic_set(&lport->xmt_fcp_wqerr, 0);
		atomic_set(&lport->xmt_fcp_abort, 0);
		atomic_set(&lport->xmt_ls_abort, 0);
		atomic_set(&lport->xmt_ls_err, 0);
		atomic_set(&lport->cmpl_fcp_xb, 0);
		atomic_set(&lport->cmpl_fcp_err, 0);
		atomic_set(&lport->cmpl_ls_xb, 0);
		atomic_set(&lport->cmpl_ls_err, 0);
		atomic_set(&lport->fc4NvmeLsRequests, 0);
		atomic_set(&lport->fc4NvmeLsCmpls, 0);
	}

	return ret;
}