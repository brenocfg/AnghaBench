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
struct venc_vpu_inst {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; scalar_t__ failure; scalar_t__ signaled; int /*<<< orphan*/  wq_hd; } ;
struct venc_ap_ipi_msg_init {unsigned long venc_inst; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  AP_IPIMSG_ENC_INIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct venc_ap_ipi_msg_init*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_vpu_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vpu_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vpu_inst*,char*,...) ; 
 int /*<<< orphan*/  vpu_enc_ipi_handler ; 
 scalar_t__ vpu_enc_send_msg (struct venc_vpu_inst*,struct venc_ap_ipi_msg_init*,int) ; 
 int vpu_ipi_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vpu_enc_init(struct venc_vpu_inst *vpu)
{
	int status;
	struct venc_ap_ipi_msg_init out;

	mtk_vcodec_debug_enter(vpu);

	init_waitqueue_head(&vpu->wq_hd);
	vpu->signaled = 0;
	vpu->failure = 0;

	status = vpu_ipi_register(vpu->dev, vpu->id, vpu_enc_ipi_handler,
				  NULL, NULL);
	if (status) {
		mtk_vcodec_err(vpu, "vpu_ipi_register fail %d", status);
		return -EINVAL;
	}

	memset(&out, 0, sizeof(out));
	out.msg_id = AP_IPIMSG_ENC_INIT;
	out.venc_inst = (unsigned long)vpu;
	if (vpu_enc_send_msg(vpu, &out, sizeof(out))) {
		mtk_vcodec_err(vpu, "AP_IPIMSG_ENC_INIT fail");
		return -EINVAL;
	}

	mtk_vcodec_debug_leave(vpu);

	return 0;
}