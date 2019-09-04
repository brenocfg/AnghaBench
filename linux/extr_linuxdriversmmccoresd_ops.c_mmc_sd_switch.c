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
typedef  int u8 ;
struct scatterlist {int dummy; } ;
struct mmc_request {struct mmc_data* data; struct mmc_command* cmd; } ;
struct mmc_data {int blksz; int blocks; int sg_len; int error; struct scatterlist* sg; int /*<<< orphan*/  flags; } ;
struct mmc_command {int arg; int flags; int error; int /*<<< orphan*/  opcode; } ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int MMC_CMD_ADTC ; 
 int /*<<< orphan*/  MMC_DATA_READ ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R1 ; 
 int /*<<< orphan*/  SD_SWITCH ; 
 int /*<<< orphan*/  mmc_set_data_timeout (struct mmc_data*,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_wait_for_req (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int*,int) ; 

int mmc_sd_switch(struct mmc_card *card, int mode, int group,
	u8 value, u8 *resp)
{
	struct mmc_request mrq = {};
	struct mmc_command cmd = {};
	struct mmc_data data = {};
	struct scatterlist sg;

	/* NOTE: caller guarantees resp is heap-allocated */

	mode = !!mode;
	value &= 0xF;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_SWITCH;
	cmd.arg = mode << 31 | 0x00FFFFFF;
	cmd.arg &= ~(0xF << (group * 4));
	cmd.arg |= value << (group * 4);
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 64;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, resp, 64);

	mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(card->host, &mrq);

	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	return 0;
}