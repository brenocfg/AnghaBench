#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmc_test_card {TYPE_1__* card; } ;
struct mmc_command {int arg; int flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int rca; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R2 ; 
 int /*<<< orphan*/  MMC_SEND_STATUS ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_test_send_status(struct mmc_test_card *test,
				struct mmc_command *cmd)
{
	memset(cmd, 0, sizeof(*cmd));

	cmd->opcode = MMC_SEND_STATUS;
	if (!mmc_host_is_spi(test->card->host))
		cmd->arg = test->card->rca << 16;
	cmd->flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_AC;

	return mmc_wait_for_cmd(test->card->host, cmd, 0);
}