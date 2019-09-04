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
struct mmc_host {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  ocr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_go_idle (struct mmc_host*) ; 
 int mmc_sdio_init_card (struct mmc_host*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mmc_send_if_cond (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int mmc_send_io_op_cond (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_reset (struct mmc_host*) ; 

__attribute__((used)) static int mmc_sdio_reinit_card(struct mmc_host *host, bool powered_resume)
{
	int ret;

	sdio_reset(host);
	mmc_go_idle(host);
	mmc_send_if_cond(host, host->card->ocr);

	ret = mmc_send_io_op_cond(host, 0, NULL);
	if (ret)
		return ret;

	return mmc_sdio_init_card(host, host->card->ocr, host->card,
				  powered_resume);
}