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
typedef  int u32 ;
struct bcm2835_host {int /*<<< orphan*/  blocks; TYPE_1__* data; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDHSTS ; 
 int SDHSTS_CMD_TIME_OUT ; 
 int SDHSTS_CRC16_ERROR ; 
 int SDHSTS_CRC7_ERROR ; 
 int SDHSTS_FIFO_ERROR ; 
 int SDHSTS_REW_TIME_OUT ; 
 int bcm2835_sdhost_read (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_sdhost_read_block_pio (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write_block_pio (struct bcm2835_host*) ; 
 int /*<<< orphan*/  log_event (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void bcm2835_sdhost_transfer_pio(struct bcm2835_host *host)
{
	u32 sdhsts;
	bool is_read;
	BUG_ON(!host->data);
	log_event("XFP<", host->data, host->blocks);

	is_read = (host->data->flags & MMC_DATA_READ) != 0;
	if (is_read)
		bcm2835_sdhost_read_block_pio(host);
	else
		bcm2835_sdhost_write_block_pio(host);

	sdhsts = bcm2835_sdhost_read(host, SDHSTS);
	if (sdhsts & (SDHSTS_CRC16_ERROR |
		      SDHSTS_CRC7_ERROR |
		      SDHSTS_FIFO_ERROR)) {
		pr_err("%s: %s transfer error - HSTS %x\n",
		       mmc_hostname(host->mmc),
		       is_read ? "read" : "write",
		       sdhsts);
		host->data->error = -EILSEQ;
	} else if ((sdhsts & (SDHSTS_CMD_TIME_OUT |
			      SDHSTS_REW_TIME_OUT))) {
		pr_err("%s: %s timeout error - HSTS %x\n",
		       mmc_hostname(host->mmc),
		       is_read ? "read" : "write",
		       sdhsts);
		host->data->error = -ETIMEDOUT;
	}
	log_event("XFP>", host->data, host->blocks);
}