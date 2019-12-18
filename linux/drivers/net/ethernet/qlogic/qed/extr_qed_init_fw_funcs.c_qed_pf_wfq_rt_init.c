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
typedef  int u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct qed_qm_pf_rt_init_params {size_t num_pf_pqs; size_t num_vf_pqs; int pf_id; int /*<<< orphan*/  max_phys_tcs_per_port; int /*<<< orphan*/  pf_wfq; struct init_qm_pq_params* pq_params; } ;
struct qed_hwfn {int dummy; } ;
struct init_qm_pq_params {int /*<<< orphan*/  tc_id; int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int MAX_NUM_PFS_BB ; 
 int /*<<< orphan*/  OVERWRITE_RT_REG (struct qed_hwfn*,int,int) ; 
 int QM_REG_WFQPFCRD_MSB_RT_OFFSET ; 
 int QM_REG_WFQPFCRD_RT_OFFSET ; 
 scalar_t__ QM_REG_WFQPFUPPERBOUND_RT_OFFSET ; 
 scalar_t__ QM_REG_WFQPFWEIGHT_RT_OFFSET ; 
 scalar_t__ QM_WFQ_CRD_REG_SIGN_BIT ; 
 int QM_WFQ_INC_VAL (int /*<<< orphan*/ ) ; 
 int QM_WFQ_MAX_INC_VAL ; 
 int QM_WFQ_UPPER_BOUND ; 
 int /*<<< orphan*/  STORE_RT_REG (struct qed_hwfn*,scalar_t__,int) ; 
 int qed_get_ext_voq (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_pf_wfq_rt_init(struct qed_hwfn *p_hwfn,

			      struct qed_qm_pf_rt_init_params *p_params)
{
	u16 num_tx_pqs = p_params->num_pf_pqs + p_params->num_vf_pqs;
	struct init_qm_pq_params *pq_params = p_params->pq_params;
	u32 inc_val, crd_reg_offset;
	u8 ext_voq;
	u16 i;

	inc_val = QM_WFQ_INC_VAL(p_params->pf_wfq);
	if (!inc_val || inc_val > QM_WFQ_MAX_INC_VAL) {
		DP_NOTICE(p_hwfn, "Invalid PF WFQ weight configuration\n");
		return -1;
	}

	for (i = 0; i < num_tx_pqs; i++) {
		ext_voq = qed_get_ext_voq(p_hwfn,
					  pq_params[i].port_id,
					  pq_params[i].tc_id,
					  p_params->max_phys_tcs_per_port);
		crd_reg_offset =
			(p_params->pf_id < MAX_NUM_PFS_BB ?
			 QM_REG_WFQPFCRD_RT_OFFSET :
			 QM_REG_WFQPFCRD_MSB_RT_OFFSET) +
			ext_voq * MAX_NUM_PFS_BB +
			(p_params->pf_id % MAX_NUM_PFS_BB);
		OVERWRITE_RT_REG(p_hwfn,
				 crd_reg_offset, (u32)QM_WFQ_CRD_REG_SIGN_BIT);
	}

	STORE_RT_REG(p_hwfn,
		     QM_REG_WFQPFUPPERBOUND_RT_OFFSET + p_params->pf_id,
		     QM_WFQ_UPPER_BOUND | (u32)QM_WFQ_CRD_REG_SIGN_BIT);
	STORE_RT_REG(p_hwfn, QM_REG_WFQPFWEIGHT_RT_OFFSET + p_params->pf_id,
		     inc_val);

	return 0;
}