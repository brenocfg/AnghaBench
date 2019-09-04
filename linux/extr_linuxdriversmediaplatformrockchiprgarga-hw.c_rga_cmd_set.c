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
struct rockchip_rga {int /*<<< orphan*/  cmdbuf_phy; int /*<<< orphan*/  dev; int /*<<< orphan*/  dst_mmu_pages; int /*<<< orphan*/  src_mmu_pages; int /*<<< orphan*/  cmdbuf_virt; } ;
struct rga_ctx {struct rockchip_rga* rga; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RGA_CMDBUF_SIZE ; 
 int /*<<< orphan*/  RGA_CMD_BASE ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rga_cmd_set_dst_addr (struct rga_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rga_cmd_set_mode (struct rga_ctx*) ; 
 int /*<<< orphan*/  rga_cmd_set_src1_addr (struct rga_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rga_cmd_set_src_addr (struct rga_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rga_cmd_set_trans_info (struct rga_ctx*) ; 
 int /*<<< orphan*/  rga_write (struct rockchip_rga*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rga_cmd_set(struct rga_ctx *ctx)
{
	struct rockchip_rga *rga = ctx->rga;

	memset(rga->cmdbuf_virt, 0, RGA_CMDBUF_SIZE * 4);

	rga_cmd_set_src_addr(ctx, rga->src_mmu_pages);
	/*
	 * Due to hardware bug,
	 * src1 mmu also should be configured when using alpha blending.
	 */
	rga_cmd_set_src1_addr(ctx, rga->dst_mmu_pages);

	rga_cmd_set_dst_addr(ctx, rga->dst_mmu_pages);
	rga_cmd_set_mode(ctx);

	rga_cmd_set_trans_info(ctx);

	rga_write(rga, RGA_CMD_BASE, rga->cmdbuf_phy);

	/* sync CMD buf for RGA */
	dma_sync_single_for_device(rga->dev, rga->cmdbuf_phy,
		PAGE_SIZE, DMA_BIDIRECTIONAL);
}