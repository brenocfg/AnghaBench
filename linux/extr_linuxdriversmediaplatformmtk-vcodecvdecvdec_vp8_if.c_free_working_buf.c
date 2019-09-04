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
struct mtk_vcodec_mem {scalar_t__ va; } ;
struct vdec_vp8_inst {TYPE_2__* vsi; int /*<<< orphan*/  ctx; struct mtk_vcodec_mem working_buf; } ;
struct TYPE_3__ {scalar_t__ working_buf_dma; } ;
struct TYPE_4__ {TYPE_1__ dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static void free_working_buf(struct vdec_vp8_inst *inst)
{
	struct mtk_vcodec_mem *mem = &inst->working_buf;

	if (mem->va)
		mtk_vcodec_mem_free(inst->ctx, mem);

	inst->vsi->dec.working_buf_dma = 0;
}