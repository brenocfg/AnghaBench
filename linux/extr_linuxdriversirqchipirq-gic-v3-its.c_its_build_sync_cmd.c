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
struct its_node {int dummy; } ;
struct its_collection {int /*<<< orphan*/  target_address; } ;
struct its_cmd_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_SYNC ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_target (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 

__attribute__((used)) static void its_build_sync_cmd(struct its_node *its,
			       struct its_cmd_block *sync_cmd,
			       struct its_collection *sync_col)
{
	its_encode_cmd(sync_cmd, GITS_CMD_SYNC);
	its_encode_target(sync_cmd, sync_col->target_address);

	its_fixup_cmd(sync_cmd);
}