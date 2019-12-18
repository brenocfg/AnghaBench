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
struct mmc_command {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ MMC_READ_SINGLE_BLOCK ; 
 scalar_t__ MMC_WRITE_BLOCK ; 
 scalar_t__ mmc_op_multi (scalar_t__) ; 

__attribute__((used)) static inline int sd_rw_cmd(struct mmc_command *cmd)
{
	return mmc_op_multi(cmd->opcode) ||
		(cmd->opcode == MMC_READ_SINGLE_BLOCK) ||
		(cmd->opcode == MMC_WRITE_BLOCK);
}