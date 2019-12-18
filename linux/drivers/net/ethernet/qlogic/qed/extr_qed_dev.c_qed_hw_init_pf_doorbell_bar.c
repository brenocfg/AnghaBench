#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct qed_ptt {int dummy; } ;
struct TYPE_3__ {int roce_edpm_mode; int min_dpis; } ;
struct TYPE_4__ {TYPE_1__ rdma_pf_params; } ;
struct qed_hwfn {int num_hwfns; int dpi_count; int dpi_start_offset; TYPE_2__ pf_params; int /*<<< orphan*/  dpi_size; scalar_t__ wid_count; scalar_t__ dcbx_no_edpm; struct qed_hwfn* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_ID_1 ; 
 int /*<<< orphan*/  DORQ_REG_PF_ICID_BIT_SHIFT_NORM ; 
 int /*<<< orphan*/  DORQ_REG_PF_MIN_ADDR_REG1 ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int,int,...) ; 
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,int,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PROTOCOLID_CORE ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int QED_MIN_PWM_REGION ; 
 int QED_PF_DEMS_SIZE ; 
 int QED_ROCE_EDPM_MODE_DISABLE ; 
 int QED_ROCE_EDPM_MODE_ENABLE ; 
 int QED_ROCE_EDPM_MODE_FORCE_ON ; 
 int ilog2 (int) ; 
 int num_present_cpus () ; 
 int qed_cxt_get_proto_cid_count (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qed_cxt_get_proto_cid_start (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_edpm_enabled (struct qed_hwfn*) ; 
 int qed_hw_bar_size (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int qed_hw_init_dpi_size (struct qed_hwfn*,struct qed_ptt*,int,int) ; 
 int /*<<< orphan*/  qed_rdma_dpm_bar (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 int roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qed_hw_init_pf_doorbell_bar(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 pwm_regsize, norm_regsize;
	u32 non_pwm_conn, min_addr_reg1;
	u32 db_bar_size, n_cpus = 1;
	u32 roce_edpm_mode;
	u32 pf_dems_shift;
	int rc = 0;
	u8 cond;

	db_bar_size = qed_hw_bar_size(p_hwfn, p_ptt, BAR_ID_1);
	if (p_hwfn->cdev->num_hwfns > 1)
		db_bar_size /= 2;

	/* Calculate doorbell regions */
	non_pwm_conn = qed_cxt_get_proto_cid_start(p_hwfn, PROTOCOLID_CORE) +
		       qed_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_CORE,
						   NULL) +
		       qed_cxt_get_proto_cid_count(p_hwfn, PROTOCOLID_ETH,
						   NULL);
	norm_regsize = roundup(QED_PF_DEMS_SIZE * non_pwm_conn, PAGE_SIZE);
	min_addr_reg1 = norm_regsize / 4096;
	pwm_regsize = db_bar_size - norm_regsize;

	/* Check that the normal and PWM sizes are valid */
	if (db_bar_size < norm_regsize) {
		DP_ERR(p_hwfn->cdev,
		       "Doorbell BAR size 0x%x is too small (normal region is 0x%0x )\n",
		       db_bar_size, norm_regsize);
		return -EINVAL;
	}

	if (pwm_regsize < QED_MIN_PWM_REGION) {
		DP_ERR(p_hwfn->cdev,
		       "PWM region size 0x%0x is too small. Should be at least 0x%0x (Doorbell BAR size is 0x%x and normal region size is 0x%0x)\n",
		       pwm_regsize,
		       QED_MIN_PWM_REGION, db_bar_size, norm_regsize);
		return -EINVAL;
	}

	/* Calculate number of DPIs */
	roce_edpm_mode = p_hwfn->pf_params.rdma_pf_params.roce_edpm_mode;
	if ((roce_edpm_mode == QED_ROCE_EDPM_MODE_ENABLE) ||
	    ((roce_edpm_mode == QED_ROCE_EDPM_MODE_FORCE_ON))) {
		/* Either EDPM is mandatory, or we are attempting to allocate a
		 * WID per CPU.
		 */
		n_cpus = num_present_cpus();
		rc = qed_hw_init_dpi_size(p_hwfn, p_ptt, pwm_regsize, n_cpus);
	}

	cond = (rc && (roce_edpm_mode == QED_ROCE_EDPM_MODE_ENABLE)) ||
	       (roce_edpm_mode == QED_ROCE_EDPM_MODE_DISABLE);
	if (cond || p_hwfn->dcbx_no_edpm) {
		/* Either EDPM is disabled from user configuration, or it is
		 * disabled via DCBx, or it is not mandatory and we failed to
		 * allocated a WID per CPU.
		 */
		n_cpus = 1;
		rc = qed_hw_init_dpi_size(p_hwfn, p_ptt, pwm_regsize, n_cpus);

		if (cond)
			qed_rdma_dpm_bar(p_hwfn, p_ptt);
	}

	p_hwfn->wid_count = (u16) n_cpus;

	DP_INFO(p_hwfn,
		"doorbell bar: normal_region_size=%d, pwm_region_size=%d, dpi_size=%d, dpi_count=%d, roce_edpm=%s, page_size=%lu\n",
		norm_regsize,
		pwm_regsize,
		p_hwfn->dpi_size,
		p_hwfn->dpi_count,
		(!qed_edpm_enabled(p_hwfn)) ?
		"disabled" : "enabled", PAGE_SIZE);

	if (rc) {
		DP_ERR(p_hwfn,
		       "Failed to allocate enough DPIs. Allocated %d but the current minimum is %d.\n",
		       p_hwfn->dpi_count,
		       p_hwfn->pf_params.rdma_pf_params.min_dpis);
		return -EINVAL;
	}

	p_hwfn->dpi_start_offset = norm_regsize;

	/* DEMS size is configured log2 of DWORDs, hence the division by 4 */
	pf_dems_shift = ilog2(QED_PF_DEMS_SIZE / 4);
	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_ICID_BIT_SHIFT_NORM, pf_dems_shift);
	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_MIN_ADDR_REG1, min_addr_reg1);

	return 0;
}