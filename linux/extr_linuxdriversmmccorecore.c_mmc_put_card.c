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
struct mmc_host {struct mmc_ctx* claimer; } ;
struct mmc_ctx {int dummy; } ;
struct mmc_card {int /*<<< orphan*/  dev; struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

void mmc_put_card(struct mmc_card *card, struct mmc_ctx *ctx)
{
	struct mmc_host *host = card->host;

	WARN_ON(ctx && host->claimer != ctx);

	mmc_release_host(host);
	pm_runtime_mark_last_busy(&card->dev);
	pm_runtime_put_autosuspend(&card->dev);
}