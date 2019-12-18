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
typedef  void* u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct creq_query_func_resp_sb {scalar_t__ max_qp_rd_atom; scalar_t__ max_qp_init_rd_atom; int max_sge; int l2_db_space_size; int /*<<< orphan*/ * tqm_alloc_reqs; int /*<<< orphan*/  max_gid; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_pkeys; int /*<<< orphan*/  max_srq_sge; int /*<<< orphan*/  max_srq_wr; int /*<<< orphan*/  max_srq; int /*<<< orphan*/  max_map_per_fmr; int /*<<< orphan*/  max_fmr; int /*<<< orphan*/  max_ah; int /*<<< orphan*/  max_raw_eth_qp; int /*<<< orphan*/  max_mr_size; int /*<<< orphan*/  max_mw; int /*<<< orphan*/  max_mr; int /*<<< orphan*/  max_cqe; int /*<<< orphan*/  max_cq; int /*<<< orphan*/  max_qp_wr; int /*<<< orphan*/  max_qp; } ;
struct creq_query_func_resp {int dummy; } ;
struct cmdq_query_func {int resp_size; } ;
struct bnxt_qplib_rcfw_sbuf {struct creq_query_func_resp_sb* sb; } ;
struct bnxt_qplib_rcfw {TYPE_2__* res; TYPE_1__* pdev; } ;
struct bnxt_qplib_dev_attr {int max_qp; int max_qp_sges; int max_cq_sges; int max_pd; int max_pkey; int l2_db_size; int is_atomic; void** tqm_alloc_reqs; int /*<<< orphan*/  fw_ver; void* max_sgid; void* max_inline_data; int /*<<< orphan*/  max_srq_sges; void* max_srq_wqes; void* max_srq; int /*<<< orphan*/  max_map_per_fmr; void* max_fmr; void* max_ah; void* max_raw_ethy_qp; int /*<<< orphan*/  max_mr_size; void* max_mw; void* max_mr; void* max_cq_wqes; void* max_cq; void* max_qp_wqes; scalar_t__ max_qp_init_rd_atom; scalar_t__ max_qp_rd_atom; } ;
struct TYPE_4__ {int /*<<< orphan*/  cctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNXT_QPLIB_CMDQE_UNITS ; 
 scalar_t__ BNXT_QPLIB_MAX_OUT_RD_ATOM ; 
 scalar_t__ BNXT_QPLIB_RESERVED_QP_WRS ; 
 int ENOMEM ; 
 int MAX_TQM_ALLOC_REQ ; 
 int /*<<< orphan*/  QUERY_FUNC ; 
 int /*<<< orphan*/  RCFW_CMD_PREP (struct cmdq_query_func,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RCFW_DBR_BASE_PAGE_SHIFT ; 
 scalar_t__ bnxt_qplib_is_chip_gen_p5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_qplib_query_version (struct bnxt_qplib_rcfw*,int /*<<< orphan*/ ) ; 
 struct bnxt_qplib_rcfw_sbuf* bnxt_qplib_rcfw_alloc_sbuf (struct bnxt_qplib_rcfw*,int) ; 
 int /*<<< orphan*/  bnxt_qplib_rcfw_free_sbuf (struct bnxt_qplib_rcfw*,struct bnxt_qplib_rcfw_sbuf*) ; 
 int bnxt_qplib_rcfw_send_message (struct bnxt_qplib_rcfw*,void*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

int bnxt_qplib_get_dev_attr(struct bnxt_qplib_rcfw *rcfw,
			    struct bnxt_qplib_dev_attr *attr, bool vf)
{
	struct cmdq_query_func req;
	struct creq_query_func_resp resp;
	struct bnxt_qplib_rcfw_sbuf *sbuf;
	struct creq_query_func_resp_sb *sb;
	u16 cmd_flags = 0;
	u32 temp;
	u8 *tqm_alloc;
	int i, rc = 0;

	RCFW_CMD_PREP(req, QUERY_FUNC, cmd_flags);

	sbuf = bnxt_qplib_rcfw_alloc_sbuf(rcfw, sizeof(*sb));
	if (!sbuf) {
		dev_err(&rcfw->pdev->dev,
			"SP: QUERY_FUNC alloc side buffer failed\n");
		return -ENOMEM;
	}

	sb = sbuf->sb;
	req.resp_size = sizeof(*sb) / BNXT_QPLIB_CMDQE_UNITS;
	rc = bnxt_qplib_rcfw_send_message(rcfw, (void *)&req, (void *)&resp,
					  (void *)sbuf, 0);
	if (rc)
		goto bail;

	/* Extract the context from the side buffer */
	attr->max_qp = le32_to_cpu(sb->max_qp);
	/* max_qp value reported by FW for PF doesn't include the QP1 for PF */
	if (!vf)
		attr->max_qp += 1;
	attr->max_qp_rd_atom =
		sb->max_qp_rd_atom > BNXT_QPLIB_MAX_OUT_RD_ATOM ?
		BNXT_QPLIB_MAX_OUT_RD_ATOM : sb->max_qp_rd_atom;
	attr->max_qp_init_rd_atom =
		sb->max_qp_init_rd_atom > BNXT_QPLIB_MAX_OUT_RD_ATOM ?
		BNXT_QPLIB_MAX_OUT_RD_ATOM : sb->max_qp_init_rd_atom;
	attr->max_qp_wqes = le16_to_cpu(sb->max_qp_wr);
	/*
	 * 128 WQEs needs to be reserved for the HW (8916). Prevent
	 * reporting the max number
	 */
	attr->max_qp_wqes -= BNXT_QPLIB_RESERVED_QP_WRS;
	attr->max_qp_sges = bnxt_qplib_is_chip_gen_p5(rcfw->res->cctx) ?
			    6 : sb->max_sge;
	attr->max_cq = le32_to_cpu(sb->max_cq);
	attr->max_cq_wqes = le32_to_cpu(sb->max_cqe);
	attr->max_cq_sges = attr->max_qp_sges;
	attr->max_mr = le32_to_cpu(sb->max_mr);
	attr->max_mw = le32_to_cpu(sb->max_mw);

	attr->max_mr_size = le64_to_cpu(sb->max_mr_size);
	attr->max_pd = 64 * 1024;
	attr->max_raw_ethy_qp = le32_to_cpu(sb->max_raw_eth_qp);
	attr->max_ah = le32_to_cpu(sb->max_ah);

	attr->max_fmr = le32_to_cpu(sb->max_fmr);
	attr->max_map_per_fmr = sb->max_map_per_fmr;

	attr->max_srq = le16_to_cpu(sb->max_srq);
	attr->max_srq_wqes = le32_to_cpu(sb->max_srq_wr) - 1;
	attr->max_srq_sges = sb->max_srq_sge;
	attr->max_pkey = le32_to_cpu(sb->max_pkeys);
	/*
	 * Some versions of FW reports more than 0xFFFF.
	 * Restrict it for now to 0xFFFF to avoid
	 * reporting trucated value
	 */
	if (attr->max_pkey > 0xFFFF) {
		/* ib_port_attr::pkey_tbl_len is u16 */
		attr->max_pkey = 0xFFFF;
	}

	attr->max_inline_data = le32_to_cpu(sb->max_inline_data);
	attr->l2_db_size = (sb->l2_db_space_size + 1) *
			    (0x01 << RCFW_DBR_BASE_PAGE_SHIFT);
	attr->max_sgid = le32_to_cpu(sb->max_gid);

	bnxt_qplib_query_version(rcfw, attr->fw_ver);

	for (i = 0; i < MAX_TQM_ALLOC_REQ / 4; i++) {
		temp = le32_to_cpu(sb->tqm_alloc_reqs[i]);
		tqm_alloc = (u8 *)&temp;
		attr->tqm_alloc_reqs[i * 4] = *tqm_alloc;
		attr->tqm_alloc_reqs[i * 4 + 1] = *(++tqm_alloc);
		attr->tqm_alloc_reqs[i * 4 + 2] = *(++tqm_alloc);
		attr->tqm_alloc_reqs[i * 4 + 3] = *(++tqm_alloc);
	}

	attr->is_atomic = false;
bail:
	bnxt_qplib_rcfw_free_sbuf(rcfw, sbuf);
	return rc;
}