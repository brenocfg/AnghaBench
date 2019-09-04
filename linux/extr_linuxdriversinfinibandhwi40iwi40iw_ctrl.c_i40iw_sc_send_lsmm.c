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
typedef  uintptr_t u64 ;
typedef  uintptr_t u32 ;
struct i40iw_qp_uk {int swqe_polarity; TYPE_1__* sq_base; } ;
struct i40iw_sc_qp {int /*<<< orphan*/  dev; struct i40iw_qp_uk qp_uk; } ;
typedef  int i40iw_stag ;
struct TYPE_2__ {uintptr_t* elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IWQPSQ_FRAG_STAG ; 
 int /*<<< orphan*/  I40IWQPSQ_OPCODE ; 
 int /*<<< orphan*/  I40IWQPSQ_STREAMMODE ; 
 int /*<<< orphan*/  I40IWQPSQ_VALID ; 
 int /*<<< orphan*/  I40IWQPSQ_WAITFORRCVPDU ; 
 int I40IWQP_OP_RDMA_SEND ; 
 int /*<<< orphan*/  I40IW_DEBUG_QP ; 
 int /*<<< orphan*/  I40IW_QP_WQE_MIN_SIZE ; 
 uintptr_t LS_64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,uintptr_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (uintptr_t*,uintptr_t) ; 
 int /*<<< orphan*/  set_64bit_val (uintptr_t*,int,uintptr_t) ; 

__attribute__((used)) static void i40iw_sc_send_lsmm(struct i40iw_sc_qp *qp,
			       void *lsmm_buf,
			       u32 size,
			       i40iw_stag stag)
{
	u64 *wqe;
	u64 header;
	struct i40iw_qp_uk *qp_uk;

	qp_uk = &qp->qp_uk;
	wqe = qp_uk->sq_base->elem;

	set_64bit_val(wqe, 0, (uintptr_t)lsmm_buf);

	set_64bit_val(wqe, 8, (size | LS_64(stag, I40IWQPSQ_FRAG_STAG)));

	set_64bit_val(wqe, 16, 0);

	header = LS_64(I40IWQP_OP_RDMA_SEND, I40IWQPSQ_OPCODE) |
		 LS_64(1, I40IWQPSQ_STREAMMODE) |
		 LS_64(1, I40IWQPSQ_WAITFORRCVPDU) |
		 LS_64(qp->qp_uk.swqe_polarity, I40IWQPSQ_VALID);

	i40iw_insert_wqe_hdr(wqe, header);

	i40iw_debug_buf(qp->dev, I40IW_DEBUG_QP, "SEND_LSMM WQE",
			wqe, I40IW_QP_WQE_MIN_SIZE);
}