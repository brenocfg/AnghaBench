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
struct mmc_host {int /*<<< orphan*/  ocr_avail; } ;
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_go_idle (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_card (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_send_if_cond (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_reset (struct mmc_host*) ; 

__attribute__((used)) static void mmc_sdio_resend_if_cond(struct mmc_host *host,
				    struct mmc_card *card)
{
	sdio_reset(host);
	mmc_go_idle(host);
	mmc_send_if_cond(host, host->ocr_avail);
	mmc_remove_card(card);
}