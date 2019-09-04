#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_mdp_vpu {scalar_t__ failure; int /*<<< orphan*/  pdev; } ;
struct mtk_mdp_ctx {TYPE_1__* mdp_dev; } ;
struct mdp_ipi_init {unsigned long ap_inst; int /*<<< orphan*/  ipi_id; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int /*<<< orphan*/  vpu_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_MDP_INIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPI_MDP ; 
 int mtk_mdp_vpu_send_msg (void*,int,struct mtk_mdp_vpu*,int /*<<< orphan*/ ) ; 
 struct mtk_mdp_ctx* vpu_to_ctx (struct mtk_mdp_vpu*) ; 

int mtk_mdp_vpu_init(struct mtk_mdp_vpu *vpu)
{
	int err;
	struct mdp_ipi_init msg;
	struct mtk_mdp_ctx *ctx = vpu_to_ctx(vpu);

	vpu->pdev = ctx->mdp_dev->vpu_dev;

	msg.msg_id = AP_MDP_INIT;
	msg.ipi_id = IPI_MDP;
	msg.ap_inst = (unsigned long)vpu;
	err = mtk_mdp_vpu_send_msg((void *)&msg, sizeof(msg), vpu, IPI_MDP);
	if (!err && vpu->failure)
		err = -EINVAL;

	return err;
}