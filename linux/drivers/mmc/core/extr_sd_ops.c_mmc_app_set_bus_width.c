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
struct mmc_command {int flags; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMC_BUS_WIDTH_1 129 
#define  MMC_BUS_WIDTH_4 128 
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int /*<<< orphan*/  SD_APP_SET_BUS_WIDTH ; 
 int /*<<< orphan*/  SD_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  SD_BUS_WIDTH_4 ; 
 int mmc_wait_for_app_cmd (int /*<<< orphan*/ ,struct mmc_card*,struct mmc_command*) ; 

int mmc_app_set_bus_width(struct mmc_card *card, int width)
{
	struct mmc_command cmd = {};

	cmd.opcode = SD_APP_SET_BUS_WIDTH;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

	switch (width) {
	case MMC_BUS_WIDTH_1:
		cmd.arg = SD_BUS_WIDTH_1;
		break;
	case MMC_BUS_WIDTH_4:
		cmd.arg = SD_BUS_WIDTH_4;
		break;
	default:
		return -EINVAL;
	}

	return mmc_wait_for_app_cmd(card->host, card, &cmd);
}