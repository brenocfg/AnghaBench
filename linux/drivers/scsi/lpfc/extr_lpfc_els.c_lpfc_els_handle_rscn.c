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
struct lpfc_vport {int load_flag; scalar_t__ num_disc_nodes; scalar_t__ fc_ns_retry; int /*<<< orphan*/  port_state; int /*<<< orphan*/  fc_rscn_id_cnt; int /*<<< orphan*/  fc_flag; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; scalar_t__ nlp_prev_state; int /*<<< orphan*/  nlp_type; } ;
struct lpfc_hba {scalar_t__ cfg_ns_query; } ;

/* Variables and functions */
 int FC_UNLOADING ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 scalar_t__ LPFC_NS_QUERY_GID_FT ; 
 scalar_t__ LPFC_NS_QUERY_GID_PT ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_FABRIC ; 
 int /*<<< orphan*/  NLP_STE_PLOGI_ISSUE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 scalar_t__ NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  NameServer_DID ; 
 int /*<<< orphan*/  lpfc_els_flush_rscn (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_els_plogi (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_issue_gidft (struct lpfc_vport*) ; 
 scalar_t__ lpfc_issue_gidpt (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 

int
lpfc_els_handle_rscn(struct lpfc_vport *vport)
{
	struct lpfc_nodelist *ndlp;
	struct lpfc_hba  *phba = vport->phba;

	/* Ignore RSCN if the port is being torn down. */
	if (vport->load_flag & FC_UNLOADING) {
		lpfc_els_flush_rscn(vport);
		return 0;
	}

	/* Start timer for RSCN processing */
	lpfc_set_disctmo(vport);

	/* RSCN processed */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0215 RSCN processed Data: x%x x%x x%x x%x\n",
			 vport->fc_flag, 0, vport->fc_rscn_id_cnt,
			 vport->port_state);

	/* To process RSCN, first compare RSCN data with NameServer */
	vport->fc_ns_retry = 0;
	vport->num_disc_nodes = 0;

	ndlp = lpfc_findnode_did(vport, NameServer_DID);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp)
	    && ndlp->nlp_state == NLP_STE_UNMAPPED_NODE) {
		/* Good ndlp, issue CT Request to NameServer.  Need to
		 * know how many gidfts were issued.  If none, then just
		 * flush the RSCN.  Otherwise, the outstanding requests
		 * need to complete.
		 */
		if (phba->cfg_ns_query == LPFC_NS_QUERY_GID_FT) {
			if (lpfc_issue_gidft(vport) > 0)
				return 1;
		} else if (phba->cfg_ns_query == LPFC_NS_QUERY_GID_PT) {
			if (lpfc_issue_gidpt(vport) > 0)
				return 1;
		} else {
			return 1;
		}
	} else {
		/* Nameserver login in question.  Revalidate. */
		if (ndlp) {
			ndlp = lpfc_enable_node(vport, ndlp,
						NLP_STE_PLOGI_ISSUE);
			if (!ndlp) {
				lpfc_els_flush_rscn(vport);
				return 0;
			}
			ndlp->nlp_prev_state = NLP_STE_UNUSED_NODE;
		} else {
			ndlp = lpfc_nlp_init(vport, NameServer_DID);
			if (!ndlp) {
				lpfc_els_flush_rscn(vport);
				return 0;
			}
			ndlp->nlp_prev_state = ndlp->nlp_state;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_PLOGI_ISSUE);
		}
		ndlp->nlp_type |= NLP_FABRIC;
		lpfc_issue_els_plogi(vport, NameServer_DID, 0);
		/* Wait for NameServer login cmpl before we can
		 * continue
		 */
		return 1;
	}

	lpfc_els_flush_rscn(vport);
	return 0;
}