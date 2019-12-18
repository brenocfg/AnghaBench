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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {TYPE_1__* ops; TYPE_2__* cqe_ops; scalar_t__ cqe_on; } ;
struct mmc_card {struct mmc_host* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cqe_off ) (struct mmc_host*) ;} ;
struct TYPE_3__ {int (* execute_tuning ) (struct mmc_host*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK ; 
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK_HS200 ; 
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_retune_enable (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 
 int stub2 (struct mmc_host*,int /*<<< orphan*/ ) ; 

int mmc_execute_tuning(struct mmc_card *card)
{
	struct mmc_host *host = card->host;
	u32 opcode;
	int err;

	if (!host->ops->execute_tuning)
		return 0;

	if (host->cqe_on)
		host->cqe_ops->cqe_off(host);

	if (mmc_card_mmc(card))
		opcode = MMC_SEND_TUNING_BLOCK_HS200;
	else
		opcode = MMC_SEND_TUNING_BLOCK;

	err = host->ops->execute_tuning(host, opcode);

	if (err)
		pr_err("%s: tuning execution failed: %d\n",
			mmc_hostname(host), err);
	else
		mmc_retune_enable(host);

	return err;
}