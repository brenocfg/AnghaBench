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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {scalar_t__ port_type; int ct_flags; int fc_flag; int fc_rscn_id_cnt; int /*<<< orphan*/  num_disc_nodes; int /*<<< orphan*/  cfg_restrict_login; } ;
struct lpfc_nodelist {int nlp_flag; scalar_t__ nlp_state; int nlp_type; int /*<<< orphan*/  nlp_fc4_type; } ;

/* Variables and functions */
 int FC_CT_RFF_ID ; 
 int FC_RSCN_MODE ; 
 scalar_t__ FC_TYPE_FCP ; 
 scalar_t__ FC_TYPE_NVME ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_CT ; 
 scalar_t__ LPFC_NPIV_PORT ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_FC4_FCP ; 
 int /*<<< orphan*/  NLP_FC4_NVME ; 
 int NLP_FCP_TARGET ; 
 int NLP_NPR_2B_DISC ; 
 int NLP_NVME_TARGET ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 scalar_t__ NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  SLI_CTNS_GFF_ID ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 scalar_t__ lpfc_rscn_payload_check (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_setup_disc_node (struct lpfc_vport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_prep_node_fc4type(struct lpfc_vport *vport, uint32_t Did, uint8_t fc4_type)
{
	struct lpfc_nodelist *ndlp;

	if ((vport->port_type != LPFC_NPIV_PORT) ||
	    (fc4_type == FC_TYPE_FCP) ||
	    !(vport->ct_flags & FC_CT_RFF_ID) || !vport->cfg_restrict_login) {

		ndlp = lpfc_setup_disc_node(vport, Did);

		if (ndlp && NLP_CHK_NODE_ACT(ndlp)) {
			lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"Parse GID_FTrsp: did:x%x flg:x%x x%x",
				Did, ndlp->nlp_flag, vport->fc_flag);

			/* By default, the driver expects to support FCP FC4 */
			if (fc4_type == FC_TYPE_FCP)
				ndlp->nlp_fc4_type |= NLP_FC4_FCP;

			if (fc4_type == FC_TYPE_NVME)
				ndlp->nlp_fc4_type |= NLP_FC4_NVME;

			lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
					 "0238 Process x%06x NameServer Rsp "
					 "Data: x%x x%x x%x x%x x%x\n", Did,
					 ndlp->nlp_flag, ndlp->nlp_fc4_type,
					 ndlp->nlp_state, vport->fc_flag,
					 vport->fc_rscn_id_cnt);

			/* if ndlp needs to be discovered and prior
			 * state of ndlp hit devloss, change state to
			 * allow rediscovery.
			 */
			if (ndlp->nlp_flag & NLP_NPR_2B_DISC &&
			    ndlp->nlp_state == NLP_STE_UNUSED_NODE) {
				lpfc_nlp_set_state(vport, ndlp,
						   NLP_STE_NPR_NODE);
			}
		} else {
			lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"Skip1 GID_FTrsp: did:x%x flg:x%x cnt:%d",
				Did, vport->fc_flag, vport->fc_rscn_id_cnt);

			lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
					 "0239 Skip x%06x NameServer Rsp "
					 "Data: x%x x%x %p\n",
					 Did, vport->fc_flag,
					 vport->fc_rscn_id_cnt, ndlp);
		}
	} else {
		if (!(vport->fc_flag & FC_RSCN_MODE) ||
		    lpfc_rscn_payload_check(vport, Did)) {
			lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"Query GID_FTrsp: did:x%x flg:x%x cnt:%d",
				Did, vport->fc_flag, vport->fc_rscn_id_cnt);

			/*
			 * This NPortID was previously a FCP/NVMe target,
			 * Don't even bother to send GFF_ID.
			 */
			ndlp = lpfc_findnode_did(vport, Did);
			if (ndlp && NLP_CHK_NODE_ACT(ndlp) &&
			    (ndlp->nlp_type &
			    (NLP_FCP_TARGET | NLP_NVME_TARGET))) {
				if (fc4_type == FC_TYPE_FCP)
					ndlp->nlp_fc4_type |= NLP_FC4_FCP;
				if (fc4_type == FC_TYPE_NVME)
					ndlp->nlp_fc4_type |= NLP_FC4_NVME;
				lpfc_setup_disc_node(vport, Did);
			} else if (lpfc_ns_cmd(vport, SLI_CTNS_GFF_ID,
				   0, Did) == 0)
				vport->num_disc_nodes++;
			else
				lpfc_setup_disc_node(vport, Did);
		} else {
			lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"Skip2 GID_FTrsp: did:x%x flg:x%x cnt:%d",
				Did, vport->fc_flag, vport->fc_rscn_id_cnt);

			lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
					 "0245 Skip x%06x NameServer Rsp "
					 "Data: x%x x%x\n", Did,
					 vport->fc_flag,
					 vport->fc_rscn_id_cnt);
		}
	}
}