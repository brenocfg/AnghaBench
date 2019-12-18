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
struct mtk_mdp_vpu {int /*<<< orphan*/  inst_addr; int /*<<< orphan*/  pdev; struct mdp_process_vsi* vsi; } ;
struct mdp_process_vsi {int dummy; } ;
struct mdp_ipi_comm_ack {int /*<<< orphan*/  vpu_inst_addr; scalar_t__ ap_inst; } ;

/* Variables and functions */
 scalar_t__ vpu_mapping_dm_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_mdp_vpu_handle_init_ack(struct mdp_ipi_comm_ack *msg)
{
	struct mtk_mdp_vpu *vpu = (struct mtk_mdp_vpu *)
					(unsigned long)msg->ap_inst;

	/* mapping VPU address to kernel virtual address */
	vpu->vsi = (struct mdp_process_vsi *)
			vpu_mapping_dm_addr(vpu->pdev, msg->vpu_inst_addr);
	vpu->inst_addr = msg->vpu_inst_addr;
}