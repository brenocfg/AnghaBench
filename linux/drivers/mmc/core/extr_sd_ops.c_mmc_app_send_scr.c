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
struct scatterlist {int dummy; } ;
struct mmc_request {struct mmc_data* data; struct mmc_command* cmd; } ;
struct mmc_data {int blksz; int blocks; int sg_len; int error; struct scatterlist* sg; int /*<<< orphan*/  flags; } ;
struct mmc_command {int flags; int error; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
struct mmc_card {void** raw_scr; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMC_CMD_ADTC ; 
 int /*<<< orphan*/  MMC_DATA_READ ; 
 int MMC_RSP_R1 ; 
 int MMC_RSP_SPI_R1 ; 
 int /*<<< orphan*/  SD_APP_SEND_SCR ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int mmc_app_cmd (int /*<<< orphan*/ ,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_set_data_timeout (struct mmc_data*,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_wait_for_req (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 

int mmc_app_send_scr(struct mmc_card *card)
{
	int err;
	struct mmc_request mrq = {};
	struct mmc_command cmd = {};
	struct mmc_data data = {};
	struct scatterlist sg;
	__be32 *scr;

	/* NOTE: caller guarantees scr is heap-allocated */

	err = mmc_app_cmd(card->host, card);
	if (err)
		return err;

	/* dma onto stack is unsafe/nonportable, but callers to this
	 * routine normally provide temporary on-stack buffers ...
	 */
	scr = kmalloc(sizeof(card->raw_scr), GFP_KERNEL);
	if (!scr)
		return -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;

	cmd.opcode = SD_APP_SEND_SCR;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blksz = 8;
	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;

	sg_init_one(&sg, scr, 8);

	mmc_set_data_timeout(&data, card);

	mmc_wait_for_req(card->host, &mrq);

	card->raw_scr[0] = be32_to_cpu(scr[0]);
	card->raw_scr[1] = be32_to_cpu(scr[1]);

	kfree(scr);

	if (cmd.error)
		return cmd.error;
	if (data.error)
		return data.error;

	return 0;
}