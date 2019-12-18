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
struct mmc_ctx {int dummy; } ;
struct mmc_card {int /*<<< orphan*/  host; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mmc_claim_host (int /*<<< orphan*/ ,struct mmc_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 

void mmc_get_card(struct mmc_card *card, struct mmc_ctx *ctx)
{
	pm_runtime_get_sync(&card->dev);
	__mmc_claim_host(card->host, ctx, NULL);
}