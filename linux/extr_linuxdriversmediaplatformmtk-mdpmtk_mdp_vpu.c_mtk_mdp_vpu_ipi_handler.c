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
struct mtk_mdp_vpu {int /*<<< orphan*/  failure; } ;
struct mtk_mdp_ctx {int /*<<< orphan*/  id; TYPE_2__* mdp_dev; } ;
struct mdp_ipi_comm_ack {int /*<<< orphan*/  status; scalar_t__ ap_inst; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  VPU_MDP_DEINIT_ACK 130 
#define  VPU_MDP_INIT_ACK 129 
#define  VPU_MDP_PROCESS_ACK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  mtk_mdp_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mdp_vpu_handle_init_ack (void*) ; 
 struct mtk_mdp_ctx* vpu_to_ctx (struct mtk_mdp_vpu*) ; 

__attribute__((used)) static void mtk_mdp_vpu_ipi_handler(void *data, unsigned int len, void *priv)
{
	unsigned int msg_id = *(unsigned int *)data;
	struct mdp_ipi_comm_ack *msg = (struct mdp_ipi_comm_ack *)data;
	struct mtk_mdp_vpu *vpu = (struct mtk_mdp_vpu *)
					(unsigned long)msg->ap_inst;
	struct mtk_mdp_ctx *ctx;

	vpu->failure = msg->status;
	if (!vpu->failure) {
		switch (msg_id) {
		case VPU_MDP_INIT_ACK:
			mtk_mdp_vpu_handle_init_ack(data);
			break;
		case VPU_MDP_DEINIT_ACK:
		case VPU_MDP_PROCESS_ACK:
			break;
		default:
			ctx = vpu_to_ctx(vpu);
			dev_err(&ctx->mdp_dev->pdev->dev,
				"handle unknown ipi msg:0x%x\n",
				msg_id);
			break;
		}
	} else {
		ctx = vpu_to_ctx(vpu);
		mtk_mdp_dbg(0, "[%d]:msg 0x%x, failure:%d", ctx->id,
			    msg_id, vpu->failure);
	}
}