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
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct TYPE_4__ {scalar_t__ personality; } ;
struct qed_hwfn {TYPE_2__* p_dcbx_info; TYPE_1__ hw_info; } ;
struct qed_dcbx_results {TYPE_3__* arr; } ;
typedef  enum qed_mib_read_type { ____Placeholder_qed_mib_read_type } qed_mib_read_type ;
struct TYPE_6__ {int tc; } ;
struct TYPE_5__ {struct qed_dcbx_results results; int /*<<< orphan*/  get; } ;

/* Variables and functions */
 size_t DCBX_PROTOCOL_ROCE ; 
 size_t DCBX_PROTOCOL_ROCE_V2 ; 
 int /*<<< orphan*/  NIG_REG_TX_EDPM_CTRL ; 
 int NIG_REG_TX_EDPM_CTRL_TX_EDPM_EN ; 
 int NIG_REG_TX_EDPM_CTRL_TX_EDPM_TC_EN_SHIFT ; 
 int QED_DCBX_OPERATIONAL_MIB ; 
 scalar_t__ QED_PCI_ETH_ROCE ; 
 int /*<<< orphan*/  qed_dcbx_aen (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  qed_dcbx_get_params (struct qed_hwfn*,int /*<<< orphan*/ *,int) ; 
 int qed_dcbx_process_mib_info (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_dcbx_read_mib (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int /*<<< orphan*/  qed_qm_reconf (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_roce_dpm_dcbx (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_sp_pf_update (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

int
qed_dcbx_mib_update_event(struct qed_hwfn *p_hwfn,
			  struct qed_ptt *p_ptt, enum qed_mib_read_type type)
{
	int rc = 0;

	rc = qed_dcbx_read_mib(p_hwfn, p_ptt, type);
	if (rc)
		return rc;

	if (type == QED_DCBX_OPERATIONAL_MIB) {
		rc = qed_dcbx_process_mib_info(p_hwfn, p_ptt);
		if (!rc) {
			/* reconfigure tcs of QM queues according
			 * to negotiation results
			 */
			qed_qm_reconf(p_hwfn, p_ptt);

			/* update storm FW with negotiation results */
			qed_sp_pf_update(p_hwfn);

			/* for roce PFs, we may want to enable/disable DPM
			 * when DCBx change occurs
			 */
			if (p_hwfn->hw_info.personality ==
			    QED_PCI_ETH_ROCE)
				qed_roce_dpm_dcbx(p_hwfn, p_ptt);
		}
	}

	qed_dcbx_get_params(p_hwfn, &p_hwfn->p_dcbx_info->get, type);

	if (type == QED_DCBX_OPERATIONAL_MIB) {
		struct qed_dcbx_results *p_data;
		u16 val;

		/* Configure in NIG which protocols support EDPM and should
		 * honor PFC.
		 */
		p_data = &p_hwfn->p_dcbx_info->results;
		val = (0x1 << p_data->arr[DCBX_PROTOCOL_ROCE].tc) |
		      (0x1 << p_data->arr[DCBX_PROTOCOL_ROCE_V2].tc);
		val <<= NIG_REG_TX_EDPM_CTRL_TX_EDPM_TC_EN_SHIFT;
		val |= NIG_REG_TX_EDPM_CTRL_TX_EDPM_EN;
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_EDPM_CTRL, val);
	}

	qed_dcbx_aen(p_hwfn, type);

	return rc;
}