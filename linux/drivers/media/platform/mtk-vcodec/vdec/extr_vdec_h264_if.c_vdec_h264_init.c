#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vdec_h264_vsi {int dummy; } ;
struct TYPE_5__ {scalar_t__ vsi; int /*<<< orphan*/  handler; struct mtk_vcodec_ctx* ctx; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct vdec_h264_inst {TYPE_2__ vpu; struct vdec_h264_vsi* vsi; struct mtk_vcodec_ctx* ctx; } ;
struct mtk_vcodec_ctx {struct vdec_h264_inst* drv_handle; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vpu_plat_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPI_VDEC_H264 ; 
 int allocate_predication_buf (struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  kfree (struct vdec_h264_inst*) ; 
 struct vdec_h264_inst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_h264_inst*,char*,struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_h264_inst*,char*,int) ; 
 int /*<<< orphan*/  vpu_dec_deinit (TYPE_2__*) ; 
 int vpu_dec_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vpu_dec_ipi_handler ; 

__attribute__((used)) static int vdec_h264_init(struct mtk_vcodec_ctx *ctx)
{
	struct vdec_h264_inst *inst = NULL;
	int err;

	inst = kzalloc(sizeof(*inst), GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_H264;
	inst->vpu.dev = ctx->dev->vpu_plat_dev;
	inst->vpu.ctx = ctx;
	inst->vpu.handler = vpu_dec_ipi_handler;

	err = vpu_dec_init(&inst->vpu);
	if (err) {
		mtk_vcodec_err(inst, "vdec_h264 init err=%d", err);
		goto error_free_inst;
	}

	inst->vsi = (struct vdec_h264_vsi *)inst->vpu.vsi;
	err = allocate_predication_buf(inst);
	if (err)
		goto error_deinit;

	mtk_vcodec_debug(inst, "H264 Instance >> %p", inst);

	ctx->drv_handle = inst;
	return 0;

error_deinit:
	vpu_dec_deinit(&inst->vpu);

error_free_inst:
	kfree(inst);
	return err;
}