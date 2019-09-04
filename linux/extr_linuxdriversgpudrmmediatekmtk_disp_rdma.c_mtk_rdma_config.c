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
struct mtk_disp_rdma {int dummy; } ;
struct mtk_ddp_comp {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DISP_REG_RDMA_FIFO_CON ; 
 int /*<<< orphan*/  DISP_REG_RDMA_SIZE_CON_0 ; 
 int /*<<< orphan*/  DISP_REG_RDMA_SIZE_CON_1 ; 
 unsigned int RDMA_FIFO_PSEUDO_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_FIFO_SIZE (struct mtk_disp_rdma*) ; 
 unsigned int RDMA_FIFO_UNDERFLOW_EN ; 
 unsigned int RDMA_OUTPUT_VALID_FIFO_THRESHOLD (unsigned int) ; 
 struct mtk_disp_rdma* comp_to_rdma (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  rdma_update_bits (struct mtk_ddp_comp*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mtk_rdma_config(struct mtk_ddp_comp *comp, unsigned int width,
			    unsigned int height, unsigned int vrefresh,
			    unsigned int bpc)
{
	unsigned int threshold;
	unsigned int reg;
	struct mtk_disp_rdma *rdma = comp_to_rdma(comp);

	rdma_update_bits(comp, DISP_REG_RDMA_SIZE_CON_0, 0xfff, width);
	rdma_update_bits(comp, DISP_REG_RDMA_SIZE_CON_1, 0xfffff, height);

	/*
	 * Enable FIFO underflow since DSI and DPI can't be blocked.
	 * Keep the FIFO pseudo size reset default of 8 KiB. Set the
	 * output threshold to 6 microseconds with 7/6 overhead to
	 * account for blanking, and with a pixel depth of 4 bytes:
	 */
	threshold = width * height * vrefresh * 4 * 7 / 1000000;
	reg = RDMA_FIFO_UNDERFLOW_EN |
	      RDMA_FIFO_PSEUDO_SIZE(RDMA_FIFO_SIZE(rdma)) |
	      RDMA_OUTPUT_VALID_FIFO_THRESHOLD(threshold);
	writel(reg, comp->regs + DISP_REG_RDMA_FIFO_CON);
}