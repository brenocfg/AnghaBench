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
struct vdec_vpu_inst {int /*<<< orphan*/  handler; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; int /*<<< orphan*/  wq; } ;
struct vdec_ap_ipi_init {unsigned long ap_inst_addr; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  AP_IPIMSG_DEC_INIT ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vdec_ap_ipi_init*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vpu_inst*,char*,...) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct vdec_vpu_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vpu_inst*,char*,int) ; 
 int vcodec_vpu_send_msg (struct vdec_vpu_inst*,void*,int) ; 
 int vpu_ipi_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int vpu_dec_init(struct vdec_vpu_inst *vpu)
{
	struct vdec_ap_ipi_init msg;
	int err;

	mtk_vcodec_debug_enter(vpu);

	init_waitqueue_head(&vpu->wq);

	err = vpu_ipi_register(vpu->dev, vpu->id, vpu->handler, "vdec", NULL);
	if (err != 0) {
		mtk_vcodec_err(vpu, "vpu_ipi_register fail status=%d", err);
		return err;
	}

	memset(&msg, 0, sizeof(msg));
	msg.msg_id = AP_IPIMSG_DEC_INIT;
	msg.ap_inst_addr = (unsigned long)vpu;

	mtk_vcodec_debug(vpu, "vdec_inst=%p", vpu);

	err = vcodec_vpu_send_msg(vpu, (void *)&msg, sizeof(msg));
	mtk_vcodec_debug(vpu, "- ret=%d", err);
	return err;
}