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
struct its_vpe {int dummy; } ;
struct its_node {int dummy; } ;
struct TYPE_3__ {TYPE_2__* vpe; } ;
struct its_cmd_desc {TYPE_1__ its_vinvall_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vpe_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_VINVALL ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_vpeid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 
 struct its_vpe* valid_vpe (struct its_node*,TYPE_2__*) ; 

__attribute__((used)) static struct its_vpe *its_build_vinvall_cmd(struct its_node *its,
					     struct its_cmd_block *cmd,
					     struct its_cmd_desc *desc)
{
	its_encode_cmd(cmd, GITS_CMD_VINVALL);
	its_encode_vpeid(cmd, desc->its_vinvall_cmd.vpe->vpe_id);

	its_fixup_cmd(cmd);

	return valid_vpe(its, desc->its_vinvall_cmd.vpe);
}