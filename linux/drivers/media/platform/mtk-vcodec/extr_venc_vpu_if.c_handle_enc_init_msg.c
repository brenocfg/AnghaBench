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
struct venc_vpu_ipi_msg_init {int /*<<< orphan*/  vpu_inst_addr; } ;
struct venc_vpu_inst {int /*<<< orphan*/  dev; int /*<<< orphan*/  vsi; int /*<<< orphan*/  inst_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  vpu_mapping_dm_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_enc_init_msg(struct venc_vpu_inst *vpu, void *data)
{
	struct venc_vpu_ipi_msg_init *msg = data;

	vpu->inst_addr = msg->vpu_inst_addr;
	vpu->vsi = vpu_mapping_dm_addr(vpu->dev, msg->vpu_inst_addr);
}