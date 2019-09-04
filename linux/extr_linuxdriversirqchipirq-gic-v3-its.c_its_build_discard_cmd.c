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
struct TYPE_3__ {int /*<<< orphan*/  event_id; TYPE_2__* dev; } ;
struct its_cmd_desc {TYPE_1__ its_discard_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_DISCARD ; 
 struct its_collection* dev_event_to_col (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_devid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_event_id (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 
 struct its_collection* valid_col (struct its_collection*) ; 

__attribute__((used)) static struct its_collection *its_build_discard_cmd(struct its_node *its,
						    struct its_cmd_block *cmd,
						    struct its_cmd_desc *desc)
{
	struct its_collection *col;

	col = dev_event_to_col(desc->its_discard_cmd.dev,
			       desc->its_discard_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_DISCARD);
	its_encode_devid(cmd, desc->its_discard_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_discard_cmd.event_id);

	its_fixup_cmd(cmd);

	return valid_col(col);
}