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
struct mtk_plane_pending_state {unsigned int addr; int pitch; unsigned int format; } ;
struct mtk_plane_state {struct mtk_plane_pending_state pending; } ;
struct mtk_disp_rdma {int dummy; } ;
struct mtk_ddp_comp {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DISP_RDMA_MEM_CON ; 
 scalar_t__ DISP_RDMA_MEM_GMC_SETTING_0 ; 
 scalar_t__ DISP_RDMA_MEM_SRC_PITCH ; 
 scalar_t__ DISP_RDMA_MEM_START_ADDR ; 
 int /*<<< orphan*/  DISP_REG_RDMA_GLOBAL_CON ; 
 int /*<<< orphan*/  DISP_REG_RDMA_SIZE_CON_0 ; 
 unsigned int DRM_FORMAT_UYVY ; 
 unsigned int DRM_FORMAT_YUYV ; 
 int /*<<< orphan*/  RDMA_MATRIX_ENABLE ; 
 int /*<<< orphan*/  RDMA_MATRIX_INT_MTX_BT601_to_RGB ; 
 int /*<<< orphan*/  RDMA_MATRIX_INT_MTX_SEL ; 
 int /*<<< orphan*/  RDMA_MEM_GMC ; 
 int /*<<< orphan*/  RDMA_MODE_MEMORY ; 
 struct mtk_disp_rdma* comp_to_rdma (struct mtk_ddp_comp*) ; 
 unsigned int rdma_fmt_convert (struct mtk_disp_rdma*,unsigned int) ; 
 int /*<<< orphan*/  rdma_update_bits (struct mtk_ddp_comp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mtk_rdma_layer_config(struct mtk_ddp_comp *comp, unsigned int idx,
				  struct mtk_plane_state *state)
{
	struct mtk_disp_rdma *rdma = comp_to_rdma(comp);
	struct mtk_plane_pending_state *pending = &state->pending;
	unsigned int addr = pending->addr;
	unsigned int pitch = pending->pitch & 0xffff;
	unsigned int fmt = pending->format;
	unsigned int con;

	con = rdma_fmt_convert(rdma, fmt);
	writel_relaxed(con, comp->regs + DISP_RDMA_MEM_CON);

	if (fmt == DRM_FORMAT_UYVY || fmt == DRM_FORMAT_YUYV) {
		rdma_update_bits(comp, DISP_REG_RDMA_SIZE_CON_0,
				 RDMA_MATRIX_ENABLE, RDMA_MATRIX_ENABLE);
		rdma_update_bits(comp, DISP_REG_RDMA_SIZE_CON_0,
				 RDMA_MATRIX_INT_MTX_SEL,
				 RDMA_MATRIX_INT_MTX_BT601_to_RGB);
	} else {
		rdma_update_bits(comp, DISP_REG_RDMA_SIZE_CON_0,
				 RDMA_MATRIX_ENABLE, 0);
	}

	writel_relaxed(addr, comp->regs + DISP_RDMA_MEM_START_ADDR);
	writel_relaxed(pitch, comp->regs + DISP_RDMA_MEM_SRC_PITCH);
	writel(RDMA_MEM_GMC, comp->regs + DISP_RDMA_MEM_GMC_SETTING_0);
	rdma_update_bits(comp, DISP_REG_RDMA_GLOBAL_CON,
			 RDMA_MODE_MEMORY, RDMA_MODE_MEMORY);
}