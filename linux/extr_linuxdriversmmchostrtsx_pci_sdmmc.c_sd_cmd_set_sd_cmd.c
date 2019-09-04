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
struct rtsx_pcr {int dummy; } ;
struct mmc_command {int opcode; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CMD0 ; 
 int /*<<< orphan*/  SD_CMD1 ; 
 int SD_CMD_START ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_pci_write_be32 (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_cmd_set_sd_cmd(struct rtsx_pcr *pcr, struct mmc_command *cmd)
{
	rtsx_pci_add_cmd(pcr, WRITE_REG_CMD, SD_CMD0, 0xFF,
		SD_CMD_START | cmd->opcode);
	rtsx_pci_write_be32(pcr, SD_CMD1, cmd->arg);
}