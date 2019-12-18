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
typedef  scalar_t__ uint16_t ;
struct lpfc_vport {int fc_flag; int fdmi_port_mask; scalar_t__ fdmi_num_disc; scalar_t__ port_type; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int FC_FABRIC ; 
 int /*<<< orphan*/  FDMI_DID ; 
 int LPFC_FDMI_PORT_ATTR_num_disc ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  SLI_MGMT_RPA ; 
 int /*<<< orphan*/  SLI_MGMT_RPRT ; 
 int /*<<< orphan*/  lpfc_fdmi_cmd (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lpfc_find_map_node (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_is_link_up (struct lpfc_hba*) ; 

void
lpfc_fdmi_num_disc_check(struct lpfc_vport *vport)
{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_nodelist *ndlp;
	uint16_t cnt;

	if (!lpfc_is_link_up(phba))
		return;

	/* Must be connected to a Fabric */
	if (!(vport->fc_flag & FC_FABRIC))
		return;

	if (!(vport->fdmi_port_mask & LPFC_FDMI_PORT_ATTR_num_disc))
		return;

	cnt = lpfc_find_map_node(vport);
	if (cnt == vport->fdmi_num_disc)
		return;

	ndlp = lpfc_findnode_did(vport, FDMI_DID);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		return;

	if (vport->port_type == LPFC_PHYSICAL_PORT) {
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RPA,
			      LPFC_FDMI_PORT_ATTR_num_disc);
	} else {
		lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_RPRT,
			      LPFC_FDMI_PORT_ATTR_num_disc);
	}
}