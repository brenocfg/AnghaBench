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
struct sdio_mmc_card {int /*<<< orphan*/  work_flags; struct sdio_func* func; } ;
struct sdio_func {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct mwifiex_adapter {struct sdio_mmc_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_IFACE_WORK_CARD_RESET ; 
 int /*<<< orphan*/  MWIFIEX_IFACE_WORK_DEVICE_DUMP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mmc_hw_reset (int /*<<< orphan*/ ) ; 
 int mwifiex_reinit_sw (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_shutdown_sw (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 

__attribute__((used)) static void mwifiex_sdio_card_reset_work(struct mwifiex_adapter *adapter)
{
	struct sdio_mmc_card *card = adapter->card;
	struct sdio_func *func = card->func;
	int ret;

	mwifiex_shutdown_sw(adapter);

	/* power cycle the adapter */
	sdio_claim_host(func);
	mmc_hw_reset(func->card->host);
	sdio_release_host(func);

	/* Previous save_adapter won't be valid after this. We will cancel
	 * pending work requests.
	 */
	clear_bit(MWIFIEX_IFACE_WORK_DEVICE_DUMP, &card->work_flags);
	clear_bit(MWIFIEX_IFACE_WORK_CARD_RESET, &card->work_flags);

	ret = mwifiex_reinit_sw(adapter);
	if (ret)
		dev_err(&func->dev, "reinit failed: %d\n", ret);
}