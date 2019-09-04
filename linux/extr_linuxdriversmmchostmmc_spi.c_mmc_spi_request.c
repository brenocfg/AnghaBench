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
struct mmc_spi_host {int /*<<< orphan*/  mmc; TYPE_1__* spi; } ;
struct mmc_request {struct mmc_command* stop; TYPE_2__* data; struct mmc_command* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {int flags; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/  blksz; } ;
struct TYPE_3__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int EINVAL ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_R1B ; 
 int MMC_RSP_SPI_R1B ; 
 int /*<<< orphan*/  MMC_STOP_TRANSMISSION ; 
 int /*<<< orphan*/  mmc_cs_off (struct mmc_spi_host*) ; 
 struct mmc_spi_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int mmc_spi_command_send (struct mmc_spi_host*,struct mmc_request*,struct mmc_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_spi_data_do (struct mmc_spi_host*,struct mmc_command*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_spi_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct mmc_spi_host	*host = mmc_priv(mmc);
	int			status = -EINVAL;
	int			crc_retry = 5;
	struct mmc_command	stop;

#ifdef DEBUG
	/* MMC core and layered drivers *MUST* issue SPI-aware commands */
	{
		struct mmc_command	*cmd;
		int			invalid = 0;

		cmd = mrq->cmd;
		if (!mmc_spi_resp_type(cmd)) {
			dev_dbg(&host->spi->dev, "bogus command\n");
			cmd->error = -EINVAL;
			invalid = 1;
		}

		cmd = mrq->stop;
		if (cmd && !mmc_spi_resp_type(cmd)) {
			dev_dbg(&host->spi->dev, "bogus STOP command\n");
			cmd->error = -EINVAL;
			invalid = 1;
		}

		if (invalid) {
			dump_stack();
			mmc_request_done(host->mmc, mrq);
			return;
		}
	}
#endif

	/* request exclusive bus access */
	spi_bus_lock(host->spi->master);

crc_recover:
	/* issue command; then optionally data and stop */
	status = mmc_spi_command_send(host, mrq, mrq->cmd, mrq->data != NULL);
	if (status == 0 && mrq->data) {
		mmc_spi_data_do(host, mrq->cmd, mrq->data, mrq->data->blksz);

		/*
		 * The SPI bus is not always reliable for large data transfers.
		 * If an occasional crc error is reported by the SD device with
		 * data read/write over SPI, it may be recovered by repeating
		 * the last SD command again. The retry count is set to 5 to
		 * ensure the driver passes stress tests.
		 */
		if (mrq->data->error == -EILSEQ && crc_retry) {
			stop.opcode = MMC_STOP_TRANSMISSION;
			stop.arg = 0;
			stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
			status = mmc_spi_command_send(host, mrq, &stop, 0);
			crc_retry--;
			mrq->data->error = 0;
			goto crc_recover;
		}

		if (mrq->stop)
			status = mmc_spi_command_send(host, mrq, mrq->stop, 0);
		else
			mmc_cs_off(host);
	}

	/* release the bus */
	spi_bus_unlock(host->spi->master);

	mmc_request_done(host->mmc, mrq);
}