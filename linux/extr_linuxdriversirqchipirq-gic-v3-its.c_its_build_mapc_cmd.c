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
struct its_node {int dummy; } ;
struct its_collection {int /*<<< orphan*/  target_address; int /*<<< orphan*/  col_id; } ;
struct TYPE_2__ {struct its_collection* col; int /*<<< orphan*/  valid; } ;
struct its_cmd_desc {TYPE_1__ its_mapc_cmd; } ;
struct its_cmd_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_MAPC ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_collection (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_target (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_valid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 

__attribute__((used)) static struct its_collection *its_build_mapc_cmd(struct its_node *its,
						 struct its_cmd_block *cmd,
						 struct its_cmd_desc *desc)
{
	its_encode_cmd(cmd, GITS_CMD_MAPC);
	its_encode_collection(cmd, desc->its_mapc_cmd.col->col_id);
	its_encode_target(cmd, desc->its_mapc_cmd.col->target_address);
	its_encode_valid(cmd, desc->its_mapc_cmd.valid);

	its_fixup_cmd(cmd);

	return desc->its_mapc_cmd.col;
}