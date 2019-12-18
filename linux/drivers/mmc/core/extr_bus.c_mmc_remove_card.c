#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_host {int cqe_enabled; TYPE_1__* cqe_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct mmc_card {TYPE_2__ dev; int /*<<< orphan*/  rca; struct mmc_host* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cqe_disable ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 scalar_t__ mmc_card_present (struct mmc_card*) ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_card_debugfs (struct mmc_card*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

void mmc_remove_card(struct mmc_card *card)
{
	struct mmc_host *host = card->host;

#ifdef CONFIG_DEBUG_FS
	mmc_remove_card_debugfs(card);
#endif

	if (host->cqe_enabled) {
		host->cqe_ops->cqe_disable(host);
		host->cqe_enabled = false;
	}

	if (mmc_card_present(card)) {
		if (mmc_host_is_spi(card->host)) {
			pr_info("%s: SPI card removed\n",
				mmc_hostname(card->host));
		} else {
			pr_info("%s: card %04x removed\n",
				mmc_hostname(card->host), card->rca);
		}
		device_del(&card->dev);
		of_node_put(card->dev.of_node);
	}

	put_device(&card->dev);
}