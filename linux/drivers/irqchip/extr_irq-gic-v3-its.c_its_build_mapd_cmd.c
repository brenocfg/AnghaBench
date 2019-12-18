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
typedef  scalar_t__ u8 ;
struct its_node {int dummy; } ;
struct its_collection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  valid; TYPE_2__* dev; } ;
struct its_cmd_desc {TYPE_1__ its_mapd_cmd; } ;
struct its_cmd_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  itt; int /*<<< orphan*/  nr_ites; } ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GITS_CMD_MAPD ; 
 int /*<<< orphan*/  ITS_ITT_ALIGN ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_cmd (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_devid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_encode_itt (struct its_cmd_block*,unsigned long) ; 
 int /*<<< orphan*/  its_encode_size (struct its_cmd_block*,scalar_t__) ; 
 int /*<<< orphan*/  its_encode_valid (struct its_cmd_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_fixup_cmd (struct its_cmd_block*) ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct its_collection *its_build_mapd_cmd(struct its_node *its,
						 struct its_cmd_block *cmd,
						 struct its_cmd_desc *desc)
{
	unsigned long itt_addr;
	u8 size = ilog2(desc->its_mapd_cmd.dev->nr_ites);

	itt_addr = virt_to_phys(desc->its_mapd_cmd.dev->itt);
	itt_addr = ALIGN(itt_addr, ITS_ITT_ALIGN);

	its_encode_cmd(cmd, GITS_CMD_MAPD);
	its_encode_devid(cmd, desc->its_mapd_cmd.dev->device_id);
	its_encode_size(cmd, size - 1);
	its_encode_itt(cmd, itt_addr);
	its_encode_valid(cmd, desc->its_mapd_cmd.valid);

	its_fixup_cmd(cmd);

	return NULL;
}