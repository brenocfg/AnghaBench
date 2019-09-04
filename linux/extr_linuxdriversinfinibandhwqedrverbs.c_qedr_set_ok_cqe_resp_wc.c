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
struct rdma_cqe_responder {int flags; int /*<<< orphan*/  imm_data_or_inv_r_Key; int /*<<< orphan*/  length; } ;
struct TYPE_2__ {void* imm_data; } ;
struct ib_wc {int /*<<< orphan*/  wc_flags; TYPE_1__ ex; int /*<<< orphan*/  opcode; void* byte_len; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_WC_RECV_RDMA_WITH_IMM ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WITH_IMM ; 
 int /*<<< orphan*/  IB_WC_WITH_INVALIDATE ; 
 int QEDR_RESP_IMM ; 
 int QEDR_RESP_INV ; 
 int QEDR_RESP_RDMA ; 
 void* cpu_to_be32 (void*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qedr_set_ok_cqe_resp_wc(struct rdma_cqe_responder *resp,
					  struct ib_wc *wc)
{
	wc->status = IB_WC_SUCCESS;
	wc->byte_len = le32_to_cpu(resp->length);

	if (resp->flags & QEDR_RESP_IMM) {
		wc->ex.imm_data = cpu_to_be32(le32_to_cpu(resp->imm_data_or_inv_r_Key));
		wc->wc_flags |= IB_WC_WITH_IMM;

		if (resp->flags & QEDR_RESP_RDMA)
			wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;

		if (resp->flags & QEDR_RESP_INV)
			return -EINVAL;

	} else if (resp->flags & QEDR_RESP_INV) {
		wc->ex.imm_data = le32_to_cpu(resp->imm_data_or_inv_r_Key);
		wc->wc_flags |= IB_WC_WITH_INVALIDATE;

		if (resp->flags & QEDR_RESP_RDMA)
			return -EINVAL;

	} else if (resp->flags & QEDR_RESP_RDMA) {
		return -EINVAL;
	}

	return 0;
}