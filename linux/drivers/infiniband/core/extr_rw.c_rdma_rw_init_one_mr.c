#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_10__ {int /*<<< orphan*/  access; TYPE_5__* mr; TYPE_2__ wr; } ;
struct rdma_rw_reg_ctx {TYPE_5__* mr; TYPE_4__ sge; TYPE_3__ reg_wr; } ;
struct ib_qp {int /*<<< orphan*/  device; int /*<<< orphan*/  rdma_mrs; int /*<<< orphan*/  integrity_en; TYPE_1__* pd; } ;
struct TYPE_12__ {int /*<<< orphan*/  length; int /*<<< orphan*/  iova; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_WR_REG_MR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int ib_map_mr_sg (TYPE_5__*,struct scatterlist*,int,int*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ib_mr_pool_get (struct ib_qp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int min (int,int) ; 
 scalar_t__ rdma_protocol_iwarp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_rw_fr_page_list_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_rw_inv_key (struct rdma_rw_reg_ctx*) ; 

__attribute__((used)) static int rdma_rw_init_one_mr(struct ib_qp *qp, u8 port_num,
		struct rdma_rw_reg_ctx *reg, struct scatterlist *sg,
		u32 sg_cnt, u32 offset)
{
	u32 pages_per_mr = rdma_rw_fr_page_list_len(qp->pd->device,
						    qp->integrity_en);
	u32 nents = min(sg_cnt, pages_per_mr);
	int count = 0, ret;

	reg->mr = ib_mr_pool_get(qp, &qp->rdma_mrs);
	if (!reg->mr)
		return -EAGAIN;

	count += rdma_rw_inv_key(reg);

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