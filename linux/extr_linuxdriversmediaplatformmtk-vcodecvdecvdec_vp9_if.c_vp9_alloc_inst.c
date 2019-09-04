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
struct mtk_vcodec_mem {int size; struct vdec_vp9_inst* va; } ;
struct vdec_vp9_inst {struct mtk_vcodec_mem mem; } ;
struct mtk_vcodec_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  mem ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mtk_vcodec_mem*,int /*<<< orphan*/ ,int) ; 
 int mtk_vcodec_mem_alloc (struct mtk_vcodec_ctx*,struct mtk_vcodec_mem*) ; 

__attribute__((used)) static struct vdec_vp9_inst *vp9_alloc_inst(struct mtk_vcodec_ctx *ctx)
{
	int result;
	struct mtk_vcodec_mem mem;
	struct vdec_vp9_inst *inst;

	memset(&mem, 0, sizeof(mem));
	mem.size = sizeof(struct vdec_vp9_inst);
	result = mtk_vcodec_mem_alloc(ctx, &mem);
	if (result)
		return NULL;

	inst = mem.va;
	inst->mem = mem;

	return inst;
}