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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct rdma_rw_ctx {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  device; TYPE_1__* pd; } ;
struct ib_device {int /*<<< orphan*/  dma_device; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {struct ib_device* device; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ib_dma_map_sg (struct ib_device*,struct scatterlist*,scalar_t__,int) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,struct scatterlist*,scalar_t__,int) ; 
 scalar_t__ is_pci_p2pdma_page (int /*<<< orphan*/ ) ; 
 int pci_p2pdma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,scalar_t__,int) ; 
 int rdma_rw_init_map_wrs (struct rdma_rw_ctx*,struct ib_qp*,struct scatterlist*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int rdma_rw_init_mr_wrs (struct rdma_rw_ctx*,struct ib_qp*,int /*<<< orphan*/ ,struct scatterlist*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int rdma_rw_init_single_wr (struct rdma_rw_ctx*,struct ib_qp*,struct scatterlist*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ rdma_rw_io_needs_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

int rdma_rw_ctx_init(struct rdma_rw_ctx *ctx, struct ib_qp *qp, u8 port_num,
		struct scatterlist *sg, u32 sg_cnt, u32 sg_offset,
		u64 remote_addr, u32 rkey, enum dma_data_direction dir)
{
	struct ib_device *dev = qp->pd->device;
	int ret;

	if (is_pci_p2pdma_page(sg_page(sg)))
		ret = pci_p2pdma_map_sg(dev->dma_device, sg, sg_cnt, dir);
	else
		ret = ib_dma_map_sg(dev, sg, sg_cnt, dir);

	if (!ret)
		return -ENOMEM;
	sg_cnt = ret;

	/*
	 * Skip to the S/G entry that sg_offset falls into:
	 */
	for (;;) {
		u32 len = sg_dma_len(sg);

		if (sg_offset < len)
			break;

		sg = sg_next(sg);
		sg_offset -= len;
		sg_cnt--;
	}

	ret = -EIO;
	if (WARN_ON_ONCE(sg_cnt == 0))
		goto out_unmap_sg;

	if (rdma_rw_io_needs_mr(qp->device, port_num, dir, sg_cnt)) {
		ret = rdma_rw_init_mr_wrs(ctx, qp, port_num, sg, sg_cnt,
				sg_offset, remote_addr, rkey, dir);
	} else if (sg_cnt > 1) {
		ret = rdma_rw_init_map_wrs(ctx, qp, sg, sg_cnt, sg_offset,
				remote_addr, rkey, dir);
	} else {
		ret = rdma_rw_init_single_wr(ctx, qp, sg, sg_offset,
				remote_addr, rkey, dir);
	}

	if (ret < 0)
		goto out_unmap_sg;
	return ret;

out_unmap_sg:
	ib_dma_unmap_sg(dev, sg, sg_cnt, dir);
	return ret;
}