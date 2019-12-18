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
struct vdec_vp9_vsi {int dummy; } ;
struct TYPE_4__ {scalar_t__ vsi; int /*<<< orphan*/  handler; struct mtk_vcodec_ctx* ctx; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct vdec_vp9_inst {TYPE_2__ vpu; struct vdec_vp9_vsi* vsi; struct mtk_vcodec_ctx* ctx; scalar_t__ total_frm_cnt; } ;
struct mtk_vcodec_ctx {struct vdec_vp9_inst* drv_handle; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vpu_plat_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IPI_VDEC_VP9 ; 
 int /*<<< orphan*/  init_all_fb_lists (struct vdec_vp9_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vp9_inst*,char*) ; 
 struct vdec_vp9_inst* vp9_alloc_inst (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  vp9_free_inst (struct vdec_vp9_inst*) ; 
 scalar_t__ vpu_dec_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vpu_dec_ipi_handler ; 

__attribute__((used)) static int vdec_vp9_init(struct mtk_vcodec_ctx *ctx)
{
	struct vdec_vp9_inst *inst;

	inst = vp9_alloc_inst(ctx);
	if (!inst)
		return -ENOMEM;

	inst->total_frm_cnt = 0;
	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_VP9;
	inst->vpu.dev = ctx->dev->vpu_plat_dev;
	inst->vpu.ctx = ctx;
	inst->vpu.handler = vpu_dec_ipi_handler;

	if (vpu_dec_init(&inst->vpu)) {
		mtk_vcodec_err(inst, "vp9_dec_vpu_init failed");
		goto err_deinit_inst;
	}

	inst->vsi = (struct vdec_vp9_vsi *)inst->vpu.vsi;
	init_all_fb_lists(inst);

	ctx->drv_handle = inst;
	return 0;

err_deinit_inst:
	vp9_free_inst(inst);

	return -EINVAL;
}