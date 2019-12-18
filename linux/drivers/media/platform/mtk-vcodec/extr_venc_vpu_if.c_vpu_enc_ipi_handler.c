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
struct venc_vpu_ipi_msg_common {int msg_id; scalar_t__ status; scalar_t__ venc_inst; } ;
struct venc_vpu_inst {int signaled; int failure; } ;

/* Variables and functions */
 scalar_t__ VENC_IPI_MSG_STATUS_OK ; 
#define  VPU_IPIMSG_ENC_DEINIT_DONE 131 
#define  VPU_IPIMSG_ENC_ENCODE_DONE 130 
#define  VPU_IPIMSG_ENC_INIT_DONE 129 
#define  VPU_IPIMSG_ENC_SET_PARAM_DONE 128 
 int /*<<< orphan*/  handle_enc_encode_msg (struct venc_vpu_inst*,void*) ; 
 int /*<<< orphan*/  handle_enc_init_msg (struct venc_vpu_inst*,void*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct venc_vpu_inst*,char*,int,struct venc_vpu_inst*,scalar_t__) ; 
 int /*<<< orphan*/  mtk_vcodec_debug_leave (struct venc_vpu_inst*) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct venc_vpu_inst*,char*,int) ; 

__attribute__((used)) static void vpu_enc_ipi_handler(void *data, unsigned int len, void *priv)
{
	struct venc_vpu_ipi_msg_common *msg = data;
	struct venc_vpu_inst *vpu =
		(struct venc_vpu_inst *)(unsigned long)msg->venc_inst;

	mtk_vcodec_debug(vpu, "msg_id %x inst %p status %d",
			 msg->msg_id, vpu, msg->status);

	switch (msg->msg_id) {
	case VPU_IPIMSG_ENC_INIT_DONE:
		handle_enc_init_msg(vpu, data);
		break;
	case VPU_IPIMSG_ENC_SET_PARAM_DONE:
		break;
	case VPU_IPIMSG_ENC_ENCODE_DONE:
		handle_enc_encode_msg(vpu, data);
		break;
	case VPU_IPIMSG_ENC_DEINIT_DONE:
		break;
	default:
		mtk_vcodec_err(vpu, "unknown msg id %x", msg->msg_id);
		break;
	}

	vpu->signaled = 1;
	vpu->failure = (msg->status != VENC_IPI_MSG_STATUS_OK);

	mtk_vcodec_debug_leave(vpu);
}