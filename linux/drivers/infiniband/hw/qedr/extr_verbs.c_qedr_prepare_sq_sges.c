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
typedef  int /*<<< orphan*/  u32 ;
struct rdma_sq_sge {void* length; void* l_key; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pbl; } ;
struct qedr_qp {TYPE_1__ sq; } ;
struct ib_send_wr {int num_sge; TYPE_2__* sg_list; } ;
struct TYPE_4__ {scalar_t__ length; scalar_t__ lkey; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 struct rdma_sq_sge* qed_chain_produce (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 qedr_prepare_sq_sges(struct qedr_qp *qp, u8 *wqe_size,
				const struct ib_send_wr *wr)
{
	u32 data_size = 0;
	int i;

	for (i = 0; i < wr->num_sge; i++) {
		struct rdma_sq_sge *sge = qed_chain_produce(&qp->sq.pbl);

		DMA_REGPAIR_LE(sge->addr, wr->sg_list[i].addr);
		sge->l_key = cpu_to_le32(wr->sg_list[i].lkey);
		sge->length = cpu_to_le32(wr->sg_list[i].length);
		data_size += wr->sg_list[i].length;
	}

	if (wqe_size)
		*wqe_size += wr->num_sge;

	return data_size;
}