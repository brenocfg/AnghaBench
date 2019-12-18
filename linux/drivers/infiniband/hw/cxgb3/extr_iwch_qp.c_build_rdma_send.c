#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* plen; void* num_sgle; TYPE_2__* sgl; scalar_t__* reserved; void* rem_stag; int /*<<< orphan*/  rdmaop; } ;
union t3_wr {TYPE_4__ send; } ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ invalidate_rkey; } ;
struct ib_send_wr {int opcode; int send_flags; int num_sge; TYPE_3__* sg_list; TYPE_1__ ex; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ lkey; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  to; void* len; void* stag; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_INV 128 
 int T3_MAX_SGE ; 
 int /*<<< orphan*/  T3_SEND ; 
 int /*<<< orphan*/  T3_SEND_WITH_INV ; 
 int /*<<< orphan*/  T3_SEND_WITH_SE ; 
 int /*<<< orphan*/  T3_SEND_WITH_SE_INV ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_rdma_send(union t3_wr *wqe, const struct ib_send_wr *wr,
			   u8 *flit_cnt)
{
	int i;
	u32 plen;

	switch (wr->opcode) {
	case IB_WR_SEND:
		if (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.rdmaop = T3_SEND_WITH_SE;
		else
			wqe->send.rdmaop = T3_SEND;
		wqe->send.rem_stag = 0;
		break;
	case IB_WR_SEND_WITH_INV:
		if (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.rdmaop = T3_SEND_WITH_SE_INV;
		else
			wqe->send.rdmaop = T3_SEND_WITH_INV;
		wqe->send.rem_stag = cpu_to_be32(wr->ex.invalidate_rkey);
		break;
	default:
		return -EINVAL;
	}
	if (wr->num_sge > T3_MAX_SGE)
		return -EINVAL;
	wqe->send.reserved[0] = 0;
	wqe->send.reserved[1] = 0;
	wqe->send.reserved[2] = 0;
	plen = 0;
	for (i = 0; i < wr->num_sge; i++) {
		if ((plen + wr->sg_list[i].length) < plen)
			return -EMSGSIZE;

		plen += wr->sg_list[i].length;
		wqe->send.sgl[i].stag = cpu_to_be32(wr->sg_list[i].lkey);
		wqe->send.sgl[i].len = cpu_to_be32(wr->sg_list[i].length);
		wqe->send.sgl[i].to = cpu_to_be64(wr->sg_list[i].addr);
	}
	wqe->send.num_sgle = cpu_to_be32(wr->num_sge);
	*flit_cnt = 4 + ((wr->num_sge) << 1);
	wqe->send.plen = cpu_to_be32(plen);
	return 0;
}