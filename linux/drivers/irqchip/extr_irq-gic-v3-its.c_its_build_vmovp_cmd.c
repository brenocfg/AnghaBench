#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct its_vpe {int dummy; } ;
struct its_node {scalar_t__ vlpi_redist_offset; } ;
struct TYPE_5__ {TYPE_3__* vpe; int /*<<< orphan*/  its_list; int /*<<< orphan*/  seq_num; TYPE_1__* col; } ;
struct its_cmd_desc {TYPE_2__ its_vmovp_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vpe_id; } ;
struct TYPE_4__ {scalar_t__ target_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_VMOVP ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_its_list (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_seq_num (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_target (struct its_cmd_block*,scalar_t__) ; 
 int /*<<< orphan*/  its_encode_vpeid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 
 struct its_vpe* valid_vpe (struct its_node*,TYPE_3__*) ; 

__attribute__((used)) static struct its_vpe *its_build_vmovp_cmd(struct its_node *its,
					   struct its_cmd_block *cmd,
					   struct its_cmd_desc *desc)
{
	u64 target;

	target = desc->its_vmovp_cmd.col->target_address + its->vlpi_redist_offset;
	its_encode_cmd(cmd, GITS_CMD_VMOVP);
	its_encode_seq_num(cmd, desc->its_vmovp_cmd.seq_num);
	its_encode_its_list(cmd, desc->its_vmovp_cmd.its_list);
	its_encode_vpeid(cmd, desc->its_vmovp_cmd.vpe->vpe_id);
	its_encode_target(cmd, target);

	its_fixup_cmd(cmd);

	return valid_vpe(its, desc->its_vmovp_cmd.vpe);
}