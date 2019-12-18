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
struct its_node {int dummy; } ;
struct its_collection {int dummy; } ;
struct TYPE_4__ {TYPE_1__* col; } ;
struct its_cmd_desc {TYPE_2__ its_mapc_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  col_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_INVALL ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_collection (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 

__attribute__((used)) static struct its_collection *its_build_invall_cmd(struct its_node *its,
						   struct its_cmd_block *cmd,
						   struct its_cmd_desc *desc)
{
	its_encode_cmd(cmd, GITS_CMD_INVALL);
	its_encode_collection(cmd, desc->its_mapc_cmd.col->col_id);

	its_fixup_cmd(cmd);

	return NULL;
}