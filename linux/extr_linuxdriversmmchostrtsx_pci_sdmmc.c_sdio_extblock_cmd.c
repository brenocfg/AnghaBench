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
struct mmc_data {int blksz; } ;
struct mmc_command {scalar_t__ opcode; } ;

/* Variables and functions */
 scalar_t__ SD_IO_RW_EXTENDED ; 

__attribute__((used)) static inline int sdio_extblock_cmd(struct mmc_command *cmd,
	struct mmc_data *data)
{
	return (cmd->opcode == SD_IO_RW_EXTENDED) && (data->blksz == 512);
}