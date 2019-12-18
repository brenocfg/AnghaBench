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
typedef  int /*<<< orphan*/  uint32_t ;
struct mtk_mdp_vpu {scalar_t__ failure; int /*<<< orphan*/  inst_addr; } ;
struct mdp_ipi_comm {unsigned long ap_inst; int /*<<< orphan*/  vpu_inst_addr; int /*<<< orphan*/  ipi_id; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPI_MDP ; 
 int mtk_mdp_vpu_send_msg (void*,int,struct mtk_mdp_vpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_vpu_send_ap_ipi(struct mtk_mdp_vpu *vpu, uint32_t msg_id)
{
	int err;
	struct mdp_ipi_comm msg;

	msg.msg_id = msg_id;
	msg.ipi_id = IPI_MDP;
	msg.vpu_inst_addr = vpu->inst_addr;
	msg.ap_inst = (unsigned long)vpu;
	err = mtk_mdp_vpu_send_msg((void *)&msg, sizeof(msg), vpu, IPI_MDP);
	if (!err && vpu->failure)
		err = -EINVAL;

	return err;
}