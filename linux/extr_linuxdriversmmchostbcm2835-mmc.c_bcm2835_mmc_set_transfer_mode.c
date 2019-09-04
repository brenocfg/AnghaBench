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
typedef  int u16 ;
struct mmc_data {int blocks; int flags; } ;
struct mmc_command {int /*<<< orphan*/  opcode; struct mmc_data* data; } ;
struct bcm2835_host {int flags; TYPE_2__* mrq; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* sbc; } ;
struct TYPE_3__ {int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SDHCI_ARGUMENT2 ; 
 int SDHCI_AUTO_CMD12 ; 
 int SDHCI_AUTO_CMD23 ; 
 int SDHCI_REQ_USE_DMA ; 
 int /*<<< orphan*/  SDHCI_TRANSFER_MODE ; 
 int SDHCI_TRNS_AUTO_CMD12 ; 
 int SDHCI_TRNS_AUTO_CMD23 ; 
 int SDHCI_TRNS_BLK_CNT_EN ; 
 int SDHCI_TRNS_DMA ; 
 int SDHCI_TRNS_MULTI ; 
 int SDHCI_TRNS_READ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bcm2835_mmc_readw (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm2835_mmc_writew (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_op_multi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_mmc_set_transfer_mode(struct bcm2835_host *host,
	struct mmc_command *cmd)
{
	u16 mode;
	struct mmc_data *data = cmd->data;

	if (data == NULL) {
		/* clear Auto CMD settings for no data CMDs */
		mode = bcm2835_mmc_readw(host, SDHCI_TRANSFER_MODE);
		bcm2835_mmc_writew(host, mode & ~(SDHCI_TRNS_AUTO_CMD12 |
				SDHCI_TRNS_AUTO_CMD23), SDHCI_TRANSFER_MODE);
		return;
	}

	WARN_ON(!host->data);

	mode = SDHCI_TRNS_BLK_CNT_EN;

	if ((mmc_op_multi(cmd->opcode) || data->blocks > 1)) {
		mode |= SDHCI_TRNS_MULTI;

		/*
		 * If we are sending CMD23, CMD12 never gets sent
		 * on successful completion (so no Auto-CMD12).
		 */
		if (!host->mrq->sbc && (host->flags & SDHCI_AUTO_CMD12))
			mode |= SDHCI_TRNS_AUTO_CMD12;
		else if (host->mrq->sbc && (host->flags & SDHCI_AUTO_CMD23)) {
			mode |= SDHCI_TRNS_AUTO_CMD23;
			bcm2835_mmc_writel(host, host->mrq->sbc->arg, SDHCI_ARGUMENT2, 5);
		}
	}

	if (data->flags & MMC_DATA_READ)
		mode |= SDHCI_TRNS_READ;
	if (host->flags & SDHCI_REQ_USE_DMA)
		mode |= SDHCI_TRNS_DMA;

	bcm2835_mmc_writew(host, mode, SDHCI_TRANSFER_MODE);
}