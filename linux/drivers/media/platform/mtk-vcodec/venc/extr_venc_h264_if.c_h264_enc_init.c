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
struct venc_h264_vsi {int dummy; } ;
struct TYPE_4__ {scalar_t__ vsi; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; struct mtk_vcodec_ctx* ctx; } ;
struct venc_h264_inst {TYPE_2__ vpu_inst; struct venc_h264_vsi* vsi; struct mtk_vcodec_ctx* ctx; int /*<<< orphan*/  hw_base; } ;
struct mtk_vcodec_ctx {struct venc_h264_inst* drv_handle; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vpu_plat_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPI_VENC_H264 ; 
 int /*<<< orphan*/  VENC_SYS ; 
 int /*<<< orphan*/  kfree (struct venc_h264_inst*) ; 
 struct venc_h264_inst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_get_reg_addr (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ) ; 
 int vpu_enc_init (TYPE_2__*) ; 

__attribute__((used)) static int h264_enc_init(struct mtk_vcodec_ctx *ctx)
{
	int ret = 0;
	struct venc_h264_inst *inst;

	inst = kzalloc(sizeof(*inst), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	inst->ctx = ctx;
	inst->vpu_inst.ctx = ctx;
	inst->vpu_inst.dev = ctx->dev->vpu_plat_dev;
	inst->vpu_inst.id = IPI_VENC_H264;
	inst->hw_base = mtk_vcodec_get_reg_addr(inst->ctx, VENC_SYS);

	mtk_vcodec_debug_enter(inst);

	ret = vpu_enc_init(&inst->vpu_inst);

	inst->vsi = (struct venc_h264_vsi *)inst->vpu_inst.vsi;

	mtk_vcodec_debug_leave(inst);

	if (ret)
		kfree(inst);
	else
		ctx->drv_handle = inst;

	return ret;
}