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
struct mtk_disp_rdma {int /*<<< orphan*/ * crtc; } ;
struct mtk_ddp_comp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_REG_RDMA_INT_ENABLE ; 
 int /*<<< orphan*/  RDMA_FRAME_END_INT ; 
 struct mtk_disp_rdma* comp_to_rdma (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  rdma_update_bits (struct mtk_ddp_comp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_rdma_disable_vblank(struct mtk_ddp_comp *comp)
{
	struct mtk_disp_rdma *rdma = comp_to_rdma(comp);

	rdma->crtc = NULL;
	rdma_update_bits(comp, DISP_REG_RDMA_INT_ENABLE, RDMA_FRAME_END_INT, 0);
}