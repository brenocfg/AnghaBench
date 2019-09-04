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
typedef  int /*<<< orphan*/  u64 ;
struct i40iw_sc_qp {int sq_pa; int rq_pa; uintptr_t hw_rq_size; uintptr_t hw_sq_size; uintptr_t sq_tph_val; uintptr_t rq_tph_val; uintptr_t qs_handle; int /*<<< orphan*/ * hw_host_ctx; } ;
struct i40iw_puda_rsrc {uintptr_t buf_size; uintptr_t cq_id; int /*<<< orphan*/  dev; struct i40iw_sc_qp qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPC_PRIVEN ; 
 int /*<<< orphan*/  I40IWQPC_QPCOMPCTX ; 
 int /*<<< orphan*/  I40IWQPC_QSHANDLE ; 
 int /*<<< orphan*/  I40IWQPC_RQSIZE ; 
 int /*<<< orphan*/  I40IWQPC_RQTPHVAL ; 
 int /*<<< orphan*/  I40IWQPC_RXCQNUM ; 
 int /*<<< orphan*/  I40IWQPC_SQSIZE ; 
 int /*<<< orphan*/  I40IWQPC_SQTPHVAL ; 
 int /*<<< orphan*/  I40IWQPC_TXCQNUM ; 
 int /*<<< orphan*/  I40IW_DEBUG_PUDA ; 
 int /*<<< orphan*/  I40IW_QP_CTX_SIZE ; 
 int /*<<< orphan*/  I40IW_UDA_QPC_MAXFRAMESIZE ; 
 int LS_64 (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_64bit_val (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void i40iw_puda_qp_setctx(struct i40iw_puda_rsrc *rsrc)
{
	struct i40iw_sc_qp *qp = &rsrc->qp;
	u64 *qp_ctx = qp->hw_host_ctx;

	set_64bit_val(qp_ctx, 8, qp->sq_pa);
	set_64bit_val(qp_ctx, 16, qp->rq_pa);

	set_64bit_val(qp_ctx, 24,
		      LS_64(qp->hw_rq_size, I40IWQPC_RQSIZE) |
		      LS_64(qp->hw_sq_size, I40IWQPC_SQSIZE));

	set_64bit_val(qp_ctx, 48, LS_64(rsrc->buf_size, I40IW_UDA_QPC_MAXFRAMESIZE));
	set_64bit_val(qp_ctx, 56, 0);
	set_64bit_val(qp_ctx, 64, 1);

	set_64bit_val(qp_ctx, 136,
		      LS_64(rsrc->cq_id, I40IWQPC_TXCQNUM) |
		      LS_64(rsrc->cq_id, I40IWQPC_RXCQNUM));

	set_64bit_val(qp_ctx, 160, LS_64(1, I40IWQPC_PRIVEN));

	set_64bit_val(qp_ctx, 168,
		      LS_64((uintptr_t)qp, I40IWQPC_QPCOMPCTX));

	set_64bit_val(qp_ctx, 176,
		      LS_64(qp->sq_tph_val, I40IWQPC_SQTPHVAL) |
		      LS_64(qp->rq_tph_val, I40IWQPC_RQTPHVAL) |
		      LS_64(qp->qs_handle, I40IWQPC_QSHANDLE));

	i40iw_debug_buf(rsrc->dev, I40IW_DEBUG_PUDA, "PUDA QP CONTEXT",
			qp_ctx, I40IW_QP_CTX_SIZE);
}