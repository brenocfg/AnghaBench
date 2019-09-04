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
struct its_node {int dummy; } ;
struct its_collection {int dummy; } ;
struct TYPE_5__ {TYPE_1__* col; int /*<<< orphan*/  event_id; TYPE_3__* dev; } ;
struct its_cmd_desc {TYPE_2__ its_movi_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  device_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  col_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_MOVI ; 
 struct its_collection* dev_event_to_col (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_collection (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_devid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_event_id (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 
 struct its_collection* valid_col (struct its_collection*) ; 

__attribute__((used)) static struct its_collection *its_build_movi_cmd(struct its_node *its,
						 struct its_cmd_block *cmd,
						 struct its_cmd_desc *desc)
{
	struct its_collection *col;

	col = dev_event_to_col(desc->its_movi_cmd.dev,
			       desc->its_movi_cmd.event_id);

	its_encode_cmd(cmd, GITS_CMD_MOVI);
	its_encode_devid(cmd, desc->its_movi_cmd.dev->device_id);
	its_encode_event_id(cmd, desc->its_movi_cmd.event_id);
	its_encode_collection(cmd, desc->its_movi_cmd.col->col_id);

	its_fixup_cmd(cmd);

	return valid_col(col);
}