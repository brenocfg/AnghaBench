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
typedef  int /*<<< orphan*/  u8 ;
struct sdricoh_host {int app_cmd; struct device* dev; } ;
struct page {int dummy; } ;
struct mmc_request {struct mmc_command* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {size_t blksz; int blocks; int flags; size_t bytes_xfered; TYPE_1__* sg; int /*<<< orphan*/  sg_len; } ;
struct mmc_command {unsigned char opcode; int error; int flags; int* resp; int /*<<< orphan*/  arg; struct mmc_data* data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int offset; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 
 int /*<<< orphan*/  R208_DATAIO ; 
 scalar_t__ R20C_RESP ; 
 int /*<<< orphan*/  R21C_STATUS ; 
 int /*<<< orphan*/  R226_BLOCKSIZE ; 
 int /*<<< orphan*/  STATUS_TRANSFER_FINISHED ; 
 int /*<<< orphan*/  TRANSFER_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/ * kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 struct sdricoh_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int sdricoh_blockio (struct sdricoh_host*,int,int /*<<< orphan*/ *,size_t) ; 
 int sdricoh_mmc_cmd (struct sdricoh_host*,unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ sdricoh_query_status (struct sdricoh_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdricoh_readb (struct sdricoh_host*,scalar_t__) ; 
 int sdricoh_readl (struct sdricoh_host*,scalar_t__) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdricoh_writew (struct sdricoh_host*,int /*<<< orphan*/ ,size_t) ; 
 struct page* sg_page (TYPE_1__*) ; 

__attribute__((used)) static void sdricoh_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct sdricoh_host *host = mmc_priv(mmc);
	struct mmc_command *cmd = mrq->cmd;
	struct mmc_data *data = cmd->data;
	struct device *dev = host->dev;
	unsigned char opcode = cmd->opcode;
	int i;

	dev_dbg(dev, "=============================\n");
	dev_dbg(dev, "sdricoh_request opcode=%i\n", opcode);

	sdricoh_writel(host, R21C_STATUS, 0x18);

	/* MMC_APP_CMDs need some special handling */
	if (host->app_cmd) {
		opcode |= 64;
		host->app_cmd = 0;
	} else if (opcode == 55)
		host->app_cmd = 1;

	/* read/write commands seem to require this */
	if (data) {
		sdricoh_writew(host, R226_BLOCKSIZE, data->blksz);
		sdricoh_writel(host, R208_DATAIO, 0);
	}

	cmd->error = sdricoh_mmc_cmd(host, opcode, cmd->arg);

	/* read response buffer */
	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			/* CRC is stripped so we need to do some shifting. */
			for (i = 0; i < 4; i++) {
				cmd->resp[i] =
				    sdricoh_readl(host,
						  R20C_RESP + (3 - i) * 4) << 8;
				if (i != 3)
					cmd->resp[i] |=
					    sdricoh_readb(host, R20C_RESP +
							  (3 - i) * 4 - 1);
			}
		} else
			cmd->resp[0] = sdricoh_readl(host, R20C_RESP);
	}

	/* transfer data */
	if (data && cmd->error == 0) {
		dev_dbg(dev, "transfer: blksz %i blocks %i sg_len %i "
			"sg length %i\n", data->blksz, data->blocks,
			data->sg_len, data->sg->length);

		/* enter data reading mode */
		sdricoh_writel(host, R21C_STATUS, 0x837f031e);
		for (i = 0; i < data->blocks; i++) {
			size_t len = data->blksz;
			u8 *buf;
			struct page *page;
			int result;
			page = sg_page(data->sg);

			buf = kmap(page) + data->sg->offset + (len * i);
			result =
				sdricoh_blockio(host,
					data->flags & MMC_DATA_READ, buf, len);
			kunmap(page);
			flush_dcache_page(page);
			if (result) {
				dev_err(dev, "sdricoh_request: cmd %i "
					"block transfer failed\n", cmd->opcode);
				cmd->error = result;
				break;
			} else
				data->bytes_xfered += len;
		}

		sdricoh_writel(host, R208_DATAIO, 1);

		if (sdricoh_query_status(host, STATUS_TRANSFER_FINISHED,
					TRANSFER_TIMEOUT)) {
			dev_err(dev, "sdricoh_request: transfer end error\n");
			cmd->error = -EINVAL;
		}
	}
	/* FIXME check busy flag */

	mmc_request_done(mmc, mrq);
	dev_dbg(dev, "=============================\n");
}