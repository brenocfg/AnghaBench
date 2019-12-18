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
struct vdec_h264_inst {int /*<<< orphan*/  vpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mv_buf (struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  free_predication_buf (struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  kfree (struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct vdec_h264_inst*) ; 
 int /*<<< orphan*/  vpu_dec_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdec_h264_deinit(void *h_vdec)
{
	struct vdec_h264_inst *inst = (struct vdec_h264_inst *)h_vdec;

	mtk_vcodec_debug_enter(inst);

	vpu_dec_deinit(&inst->vpu);
	free_predication_buf(inst);
	free_mv_buf(inst);

	kfree(inst);
}