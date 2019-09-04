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
struct vdec_vpu_ipi_init_ack {scalar_t__ vpu_inst_addr; scalar_t__ ap_inst_addr; } ;
struct vdec_vpu_inst {scalar_t__ inst_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  vsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_vpu_inst*,char*,scalar_t__) ; 
 int /*<<< orphan*/  vpu_mapping_dm_addr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void handle_init_ack_msg(struct vdec_vpu_ipi_init_ack *msg)
{
	struct vdec_vpu_inst *vpu = (struct vdec_vpu_inst *)
					(unsigned long)msg->ap_inst_addr;

	mtk_vcodec_debug(vpu, "+ ap_inst_addr = 0x%llx", msg->ap_inst_addr);

	/* mapping VPU address to kernel virtual address */
	/* the content in vsi is initialized to 0 in VPU */
	vpu->vsi = vpu_mapping_dm_addr(vpu->dev, msg->vpu_inst_addr);
	vpu->inst_addr = msg->vpu_inst_addr;

	mtk_vcodec_debug(vpu, "- vpu_inst_addr = 0x%x", vpu->inst_addr);
}