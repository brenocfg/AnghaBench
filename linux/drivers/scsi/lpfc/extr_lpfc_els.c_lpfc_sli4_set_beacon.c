#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  word9; } ;
union lpfc_sli4_cfg_shdr {TYPE_5__ request; } ;
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_sli4_cfg_mhdr {int dummy; } ;
struct lpfc_mbx_set_beacon_config {int dummy; } ;
struct lpfc_lcb_context {int /*<<< orphan*/  duration; int /*<<< orphan*/  capability; } ;
struct TYPE_18__ {scalar_t__ bv1s; } ;
struct TYPE_19__ {int physical_port; TYPE_3__ pc_sli4_params; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; TYPE_4__ sli4_hba; int /*<<< orphan*/  pport; } ;
struct TYPE_15__ {scalar_t__ word5; } ;
struct TYPE_16__ {union lpfc_sli4_cfg_shdr cfg_shdr; } ;
struct TYPE_17__ {TYPE_1__ header; } ;
struct TYPE_21__ {TYPE_14__ beacon_config; TYPE_2__ sli4_config; } ;
struct TYPE_22__ {TYPE_6__ un; } ;
struct TYPE_23__ {TYPE_7__ mqe; } ;
struct TYPE_24__ {TYPE_8__ u; int /*<<< orphan*/  mbox_cmpl; int /*<<< orphan*/  vport; void* ctx_ndlp; } ;
typedef  TYPE_9__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_VERSION_V0 ; 
 int /*<<< orphan*/  BEACON_VERSION_V1 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LCB_CAPABILITY_DURATION ; 
 int /*<<< orphan*/  LPFC_MBOX_OPCODE_SET_BEACON_CONFIG ; 
 int /*<<< orphan*/  LPFC_MBOX_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  LPFC_SLI4_MBX_EMBED ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,TYPE_14__*,int) ; 
 int /*<<< orphan*/  lpfc_els_lcb_rsp ; 
 int /*<<< orphan*/  lpfc_mbx_set_beacon_duration ; 
 int /*<<< orphan*/  lpfc_mbx_set_beacon_duration_v1 ; 
 int /*<<< orphan*/  lpfc_mbx_set_beacon_port_num ; 
 int /*<<< orphan*/  lpfc_mbx_set_beacon_port_type ; 
 int /*<<< orphan*/  lpfc_mbx_set_beacon_state ; 
 int /*<<< orphan*/  lpfc_sli4_config (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_9__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_set_beacon(struct lpfc_vport *vport,
		     struct lpfc_lcb_context *lcb_context,
		     uint32_t beacon_state)
{
	struct lpfc_hba *phba = vport->phba;
	union lpfc_sli4_cfg_shdr *cfg_shdr;
	LPFC_MBOXQ_t *mbox = NULL;
	uint32_t len;
	int rc;

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox)
		return 1;

	cfg_shdr = &mbox->u.mqe.un.sli4_config.header.cfg_shdr;
	len = sizeof(struct lpfc_mbx_set_beacon_config) -
		sizeof(struct lpfc_sli4_cfg_mhdr);
	lpfc_sli4_config(phba, mbox, LPFC_MBOX_SUBSYSTEM_COMMON,
			 LPFC_MBOX_OPCODE_SET_BEACON_CONFIG, len,
			 LPFC_SLI4_MBX_EMBED);
	mbox->ctx_ndlp = (void *)lcb_context;
	mbox->vport = phba->pport;
	mbox->mbox_cmpl = lpfc_els_lcb_rsp;
	bf_set(lpfc_mbx_set_beacon_port_num, &mbox->u.mqe.un.beacon_config,
	       phba->sli4_hba.physical_port);
	bf_set(lpfc_mbx_set_beacon_state, &mbox->u.mqe.un.beacon_config,
	       beacon_state);
	mbox->u.mqe.un.beacon_config.word5 = 0;		/* Reserved */

	/*
	 *	Check bv1s bit before issuing the mailbox
	 *	if bv1s == 1, LCB V1 supported
	 *	else, LCB V0 supported
	 */

	if (phba->sli4_hba.pc_sli4_params.bv1s) {
		/* COMMON_SET_BEACON_CONFIG_V1 */
		cfg_shdr->request.word9 = BEACON_VERSION_V1;
		lcb_context->capability |= LCB_CAPABILITY_DURATION;
		bf_set(lpfc_mbx_set_beacon_port_type,
		       &mbox->u.mqe.un.beacon_config, 0);
		bf_set(lpfc_mbx_set_beacon_duration_v1,
		       &mbox->u.mqe.un.beacon_config,
		       be16_to_cpu(lcb_context->duration));
	} else {
		/* COMMON_SET_BEACON_CONFIG_V0 */
		if (be16_to_cpu(lcb_context->duration) != 0) {
			mempool_free(mbox, phba->mbox_mem_pool);
			return 1;
		}
		cfg_shdr->request.word9 = BEACON_VERSION_V0;
		lcb_context->capability &=  ~(LCB_CAPABILITY_DURATION);
		bf_set(lpfc_mbx_set_beacon_state,
		       &mbox->u.mqe.un.beacon_config, beacon_state);
		bf_set(lpfc_mbx_set_beacon_port_type,
		       &mbox->u.mqe.un.beacon_config, 1);
		bf_set(lpfc_mbx_set_beacon_duration,
		       &mbox->u.mqe.un.beacon_config,
		       be16_to_cpu(lcb_context->duration));
	}

	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		mempool_free(mbox, phba->mbox_mem_pool);
		return 1;
	}

	return 0;
}