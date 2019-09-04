#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_14__ {int /*<<< orphan*/  access; TYPE_7__* mr; TYPE_4__ wr; } ;
struct TYPE_11__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct TYPE_12__ {TYPE_4__* next; TYPE_2__ ex; int /*<<< orphan*/  opcode; } ;
struct rdma_rw_reg_ctx {TYPE_7__* mr; TYPE_6__ sge; TYPE_5__ reg_wr; TYPE_3__ inv_wr; } ;
struct ib_qp {int /*<<< orphan*/  device; int /*<<< orphan*/  rdma_mrs; TYPE_1__* pd; } ;
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  iova; int /*<<< orphan*/  lkey; scalar_t__ need_inval; } ;
struct TYPE_10__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 
 int /*<<< orphan*/  IB_WR_REG_MR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int ib_map_mr_sg (TYPE_7__*,struct scatterlist*,int,int*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ib_mr_pool_get (struct ib_qp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int min (int,int) ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_rw_fr_page_list_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdma_rw_init_one_mr(struct ib_qp *qp, u8 port_num,
		struct rdma_rw_reg_ctx *reg, struct scatterlist *sg,
		u32 sg_cnt, u32 offset)
{
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device);
	u32 nents = min(sg_cnt, pages_per_mr);
	int count = 0, ret;

	reg->mr = ib_mr_pool_get(qp, &qp->rdma_mrs);
	if (!reg->mr)
		return -EAGAIN;

	if (reg->mr->need_inval) {
		reg->inv_wr.opcode = IB_WR_LOCAL_INV;
		reg->inv_wr.ex.invalidate_rkey = reg->mr->lkey;
		reg->inv_wr.next = &reg->reg_wr.wr;
		count++;
	} else {
		reg->inv_wr.next = NULL;
	}

	ret = ib_map_mr_sg(reg->mr, sg, nents, &offset, PAGE_SIZE);
	if (ret < 0 || ret < nents) {
		ib_mr_pool_put(qp, &qp->rdma_mrs, reg->mr);
		return -EINVAL;
	}

	reg->reg_wr.wr.opcode = IB_WR_REG_MR;
	reg->reg_wr.mr = reg->mr;
	reg->reg_wr.access = IB_ACCESS_LOCAL_WRITE;
	if (rdma_protocol_iwarp(qp->device, port_num))
		reg->reg_wr.access |= IB_ACCESS_REMOTE_WRITE;
	count++;

	reg->sge.addr = reg->mr->iova;
	reg->sge.length = reg->mr->length;
	return count;
}