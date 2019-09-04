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
struct mtk_vcodec_mem {scalar_t__ va; } ;
struct vdec_vp9_inst {int /*<<< orphan*/  ctx; struct mtk_vcodec_mem mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static void vp9_free_inst(struct vdec_vp9_inst *inst)
{
	struct mtk_vcodec_mem mem;

	mem = inst->mem;
	if (mem.va)
		mtk_vcodec_mem_free(inst->ctx, &mem);
}