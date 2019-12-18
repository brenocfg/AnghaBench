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
typedef  scalar_t__ u32 ;
struct mmc_command {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ MMC_READ_SINGLE_BLOCK ; 
 scalar_t__ MMC_WRITE_BLOCK ; 

__attribute__((used)) static inline bool single_op(struct mmc_command *cmd)
{
	u32 opcode = cmd->opcode;

	return opcode == MMC_WRITE_BLOCK ||
	       opcode == MMC_READ_SINGLE_BLOCK;
}