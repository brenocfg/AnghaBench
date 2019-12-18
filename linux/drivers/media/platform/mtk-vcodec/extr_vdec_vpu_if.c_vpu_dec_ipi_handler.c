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
struct vdec_vpu_ipi_ack {int msg_id; scalar_t__ status; scalar_t__ ap_inst_addr; } ;
struct vdec_vpu_inst {scalar_t__ failure; int signaled; } ;

/* Variables and functions */
#define  VPU_IPIMSG_DEC_DEINIT_ACK 132 
#define  VPU_IPIMSG_DEC_END_ACK 131 
#define  VPU_IPIMSG_DEC_INIT_ACK 130 
#define  VPU_IPIMSG_DEC_RESET_ACK 129 
#define  VPU_IPIMSG_DEC_START_ACK 128 
 int /*<<< orphan*/  handle_init_ack_msg (void*) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vpu_inst*,char*,int) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_vpu_inst*,char*,int) ; 

void vpu_dec_ipi_handler(void *data, unsigned int len, void *priv)
{
	struct vdec_vpu_ipi_ack *msg = data;
	struct vdec_vpu_inst *vpu = (struct vdec_vpu_inst *)
					(unsigned long)msg->ap_inst_addr;

	mtk_vcodec_debug(vpu, "+ id=%X", msg->msg_id);

	if (msg->status == 0) {
		switch (msg->msg_id) {
		case VPU_IPIMSG_DEC_INIT_ACK:
			handle_init_ack_msg(data);
			break;

		case VPU_IPIMSG_DEC_START_ACK:
		case VPU_IPIMSG_DEC_END_ACK:
		case VPU_IPIMSG_DEC_DEINIT_ACK:
		case VPU_IPIMSG_DEC_RESET_ACK:
			break;

		default:
			mtk_vcodec_err(vpu, "invalid msg=%X", msg->msg_id);
			break;
		}
	}

	mtk_vcodec_debug(vpu, "- id=%X", msg->msg_id);
	vpu->failure = msg->status;
	vpu->signaled = 1;
}