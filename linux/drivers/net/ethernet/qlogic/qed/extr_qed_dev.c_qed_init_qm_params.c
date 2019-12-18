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
typedef  scalar_t__ u16 ;
struct qed_qm_info {int vport_rl_en; int vport_wfq_en; scalar_t__ ooo_tc; int /*<<< orphan*/  max_phys_tcs_per_port; scalar_t__ start_vport; scalar_t__ start_pq; } ;
struct qed_hwfn {TYPE_1__* cdev; struct qed_qm_info qm_info; } ;
struct TYPE_2__ {scalar_t__ num_ports_in_engine; } ;

/* Variables and functions */
 scalar_t__ DCBX_TCP_OOO_K2_4PORT_TC ; 
 scalar_t__ DCBX_TCP_OOO_TC ; 
 scalar_t__ MAX_NUM_PORTS_K2 ; 
 int /*<<< orphan*/  NUM_OF_PHYS_TCS ; 
 int /*<<< orphan*/  NUM_PHYS_TCS_4PORT_K2 ; 
 int /*<<< orphan*/  QED_PQ ; 
 int /*<<< orphan*/  QED_VPORT ; 
 scalar_t__ RESC_START (struct qed_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_init_qm_params(struct qed_hwfn *p_hwfn)
{
	struct qed_qm_info *qm_info = &p_hwfn->qm_info;
	bool four_port;

	/* pq and vport bases for this PF */
	qm_info->start_pq = (u16) RESC_START(p_hwfn, QED_PQ);
	qm_info->start_vport = (u8) RESC_START(p_hwfn, QED_VPORT);

	/* rate limiting and weighted fair queueing are always enabled */
	qm_info->vport_rl_en = true;
	qm_info->vport_wfq_en = true;

	/* TC config is different for AH 4 port */
	four_port = p_hwfn->cdev->num_ports_in_engine == MAX_NUM_PORTS_K2;

	/* in AH 4 port we have fewer TCs per port */
	qm_info->max_phys_tcs_per_port = four_port ? NUM_PHYS_TCS_4PORT_K2 :
						     NUM_OF_PHYS_TCS;

	/* unless MFW indicated otherwise, ooo_tc == 3 for
	 * AH 4-port and 4 otherwise.
	 */
	if (!qm_info->ooo_tc)
		qm_info->ooo_tc = four_port ? DCBX_TCP_OOO_K2_4PORT_TC :
					      DCBX_TCP_OOO_TC;
}