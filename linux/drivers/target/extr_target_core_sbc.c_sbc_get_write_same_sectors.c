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
typedef  scalar_t__ u32 ;
struct se_cmd {scalar_t__* t_task_cdb; scalar_t__ t_task_lba; TYPE_2__* se_dev; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {TYPE_1__* transport; } ;
struct TYPE_3__ {scalar_t__ (* get_blocks ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ WRITE_SAME ; 
 scalar_t__ WRITE_SAME_16 ; 
 scalar_t__ get_unaligned_be16 (scalar_t__*) ; 
 scalar_t__ get_unaligned_be32 (scalar_t__*) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

sector_t sbc_get_write_same_sectors(struct se_cmd *cmd)
{
	u32 num_blocks;

	if (cmd->t_task_cdb[0] == WRITE_SAME)
		num_blocks = get_unaligned_be16(&cmd->t_task_cdb[7]);
	else if (cmd->t_task_cdb[0] == WRITE_SAME_16)
		num_blocks = get_unaligned_be32(&cmd->t_task_cdb[10]);
	else /* WRITE_SAME_32 via VARIABLE_LENGTH_CMD */
		num_blocks = get_unaligned_be32(&cmd->t_task_cdb[28]);

	/*
	 * Use the explicit range when non zero is supplied, otherwise calculate
	 * the remaining range based on ->get_blocks() - starting LBA.
	 */
	if (num_blocks)
		return num_blocks;

	return cmd->se_dev->transport->get_blocks(cmd->se_dev) -
		cmd->t_task_lba + 1;
}