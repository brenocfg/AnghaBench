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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_llh_filter_details {int /*<<< orphan*/  enable; int /*<<< orphan*/  hdr_sel; int /*<<< orphan*/  protocol_type; int /*<<< orphan*/  mode; int /*<<< orphan*/  value; } ;
struct qed_hwfn {int rel_pf_id; TYPE_1__* cdev; } ;
struct qed_dmae_params {int dst_pfid; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int num_ports_in_engine; } ;

/* Variables and functions */
 int MFW_PORT (struct qed_hwfn*) ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_EN ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_HDR_SEL ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_MODE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE ; 
 scalar_t__ NIG_REG_LLH_FUNC_FILTER_VALUE ; 
 int PXP_PRETEND_CONCRETE_FID_PFID_SHIFT ; 
 int /*<<< orphan*/  QED_DMAE_FLAG_PF_DST ; 
 scalar_t__ QED_IS_BB (TYPE_1__*) ; 
 int qed_dmae_host2grc (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,scalar_t__,int,struct qed_dmae_params*) ; 
 int /*<<< orphan*/  qed_fid_pretend (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qed_llh_access_filter(struct qed_hwfn *p_hwfn,
		      struct qed_ptt *p_ptt,
		      u8 abs_ppfid,
		      u8 filter_idx,
		      struct qed_llh_filter_details *p_details)
{
	struct qed_dmae_params params = {0};
	u32 addr;
	u8 pfid;
	int rc;

	/* The NIG/LLH registers that are accessed in this function have only 16
	 * rows which are exposed to a PF. I.e. only the 16 filters of its
	 * default ppfid. Accessing filters of other ppfids requires pretending
	 * to another PFs.
	 * The calculation of PPFID->PFID in AH is based on the relative index
	 * of a PF on its port.
	 * For BB the pfid is actually the abs_ppfid.
	 */
	if (QED_IS_BB(p_hwfn->cdev))
		pfid = abs_ppfid;
	else
		pfid = abs_ppfid * p_hwfn->cdev->num_ports_in_engine +
		    MFW_PORT(p_hwfn);

	/* Filter enable - should be done first when removing a filter */
	if (!p_details->enable) {
		qed_fid_pretend(p_hwfn, p_ptt,
				pfid << PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);

		addr = NIG_REG_LLH_FUNC_FILTER_EN + filter_idx * 0x4;
		qed_wr(p_hwfn, p_ptt, addr, p_details->enable);

		qed_fid_pretend(p_hwfn, p_ptt,
				p_hwfn->rel_pf_id <<
				PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);
	}

	/* Filter value */
	addr = NIG_REG_LLH_FUNC_FILTER_VALUE + 2 * filter_idx * 0x4;

	params.flags = QED_DMAE_FLAG_PF_DST;
	params.dst_pfid = pfid;
	rc = qed_dmae_host2grc(p_hwfn,
			       p_ptt,
			       (u64)(uintptr_t)&p_details->value,
			       addr, 2 /* size_in_dwords */,
			       &params);
	if (rc)
		return rc;

	qed_fid_pretend(p_hwfn, p_ptt,
			pfid << PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);

	/* Filter mode */
	addr = NIG_REG_LLH_FUNC_FILTER_MODE + filter_idx * 0x4;
	qed_wr(p_hwfn, p_ptt, addr, p_details->mode);

	/* Filter protocol type */
	addr = NIG_REG_LLH_FUNC_FILTER_PROTOCOL_TYPE + filter_idx * 0x4;
	qed_wr(p_hwfn, p_ptt, addr, p_details->protocol_type);

	/* Filter header select */
	addr = NIG_REG_LLH_FUNC_FILTER_HDR_SEL + filter_idx * 0x4;
	qed_wr(p_hwfn, p_ptt, addr, p_details->hdr_sel);

	/* Filter enable - should be done last when adding a filter */
	if (p_details->enable) {
		addr = NIG_REG_LLH_FUNC_FILTER_EN + filter_idx * 0x4;
		qed_wr(p_hwfn, p_ptt, addr, p_details->enable);
	}

	qed_fid_pretend(p_hwfn, p_ptt,
			p_hwfn->rel_pf_id <<
			PXP_PRETEND_CONCRETE_FID_PFID_SHIFT);

	return 0;
}