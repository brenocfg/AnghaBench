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
struct venc_vpu_inst {int /*<<< orphan*/  inst_addr; } ;
struct venc_ap_ipi_msg_deinit {int /*<<< orphan*/  vpu_inst_addr; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  AP_IPIMSG_ENC_DEINIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct venc_ap_ipi_msg_deinit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_enter (struct venc_vpu_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vpu_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vpu_inst*,char*) ; 
 scalar_t__ vpu_enc_send_msg (struct venc_vpu_inst*,struct venc_ap_ipi_msg_deinit*,int) ; 

int vpu_enc_deinit(struct venc_vpu_inst *vpu)
{
	struct venc_ap_ipi_msg_deinit out;

	mtk_vcodec_debug_enter(vpu);

	memset(&out, 0, sizeof(out));
	out.msg_id = AP_IPIMSG_ENC_DEINIT;
	out.vpu_inst_addr = vpu->inst_addr;
	if (vpu_enc_send_msg(vpu, &out, sizeof(out))) {
		mtk_vcodec_err(vpu, "AP_IPIMSG_ENC_DEINIT fail");
		return -EINVAL;
	}

	mtk_vcodec_debug_leave(vpu);

	return 0;
}