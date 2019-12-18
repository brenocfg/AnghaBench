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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_5__ {TYPE_3__* sges; TYPE_3__* wrs; } ;
struct rdma_rw_ctx {int type; int nr_ops; TYPE_1__ map; TYPE_3__* reg; } ;
struct ib_qp {TYPE_2__* pd; int /*<<< orphan*/  rdma_mrs; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_8__ {int /*<<< orphan*/  dma_device; } ;
struct TYPE_7__ {int /*<<< orphan*/  mr; } ;
struct TYPE_6__ {TYPE_4__* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RDMA_RW_MR 130 
#define  RDMA_RW_MULTI_WR 129 
#define  RDMA_RW_SINGLE_WR 128 
 int /*<<< orphan*/  ib_dma_unmap_sg (TYPE_4__*,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ib_mr_pool_put (struct ib_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pci_p2pdma_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_p2pdma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

void rdma_rw_ctx_destroy(struct rdma_rw_ctx *ctx, struct ib_qp *qp, u8 port_num,
		struct scatterlist *sg, u32 sg_cnt, enum dma_data_direction dir)
{
	int i;

	switch (ctx->type) {
	case RDMA_RW_MR:
		for (i = 0; i < ctx->nr_ops; i++)
			ib_mr_pool_put(qp, &qp->rdma_mrs, ctx->reg[i].mr);
		kfree(ctx->reg);
		break;
	case RDMA_RW_MULTI_WR:
		kfree(ctx->map.wrs);
		kfree(ctx->map.sges);
		break;
	case RDMA_RW_SINGLE_WR:
		break;
	default:
		BUG();
		break;
	}

	if (is_pci_p2pdma_page(sg_page(sg)))
		pci_p2pdma_unmap_sg(qp->pd->device->dma_device, sg,
				    sg_cnt, dir);
	else
		ib_dma_unmap_sg(qp->pd->device, sg, sg_cnt, dir);
}