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
typedef  int u32 ;
struct its_vpe {int dummy; } ;
struct its_node {int dummy; } ;
struct TYPE_5__ {TYPE_3__* vpe; int /*<<< orphan*/  event_id; TYPE_1__* dev; scalar_t__ db_enabled; } ;
struct its_cmd_desc {TYPE_2__ its_vmovi_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_6__ {int vpe_db_lpi; int /*<<< orphan*/  vpe_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITS_CMD_VMOVI ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_db_phys_id (struct its_cmd_block*,int) ; 
 int /*<<< orphan*/  its_encode_db_valid (struct its_cmd_block*,int) ; 
 int /*<<< orphan*/  its_encode_devid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_event_id (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_vpeid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 
 struct its_vpe* valid_vpe (struct its_node*,TYPE_3__*) ; 

__attribute__((used)) static struct its_vpe *its_build_vmovi_cmd(struct its_node *its,
					   struct its_cmd_block *cmd,
					   struct its_cmd_desc *desc)
{
	u32 db;

	if (desc->its_vmovi_cmd.db_enabled)
		db = desc->its_vmovi_cmd.vpe->vpe_db_lpi;
	else
		db = 1023;

	its_encode_cmd(cmd, GITS_CMD_VMOVI);
	its_encode_devid(cmd, desc->its_vmovi_cmd.dev->device_id);
	its_encode_vpeid(cmd, desc->its_vmovi_cmd.vpe->vpe_id);
	its_encode_event_id(cmd, desc->its_vmovi_cmd.event_id);
	its_encode_db_phys_id(cmd, db);
	its_encode_db_valid(cmd, true);

	its_fixup_cmd(cmd);

	return valid_vpe(its, desc->its_vmovi_cmd.vpe);
}