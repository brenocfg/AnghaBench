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
struct mmc_host {int caps; struct mmc_card* card; scalar_t__ ocr_avail_sdio; scalar_t__ ocr_avail; int /*<<< orphan*/  claimed; } ;
struct mmc_card {int /*<<< orphan*/  dev; TYPE_1__** sdio_func; scalar_t__ sdio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int MMC_CAP_POWER_OFF_CARD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int mmc_add_card (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_attach_bus (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_detach_bus (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int mmc_sdio_init_card (struct mmc_host*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_sdio_ops ; 
 int /*<<< orphan*/  mmc_sdio_remove (struct mmc_host*) ; 
 int mmc_select_voltage (struct mmc_host*,int) ; 
 int mmc_send_io_op_cond (struct mmc_host*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int sdio_add_func (TYPE_1__*) ; 
 int sdio_init_func (struct mmc_card*,int) ; 

int mmc_attach_sdio(struct mmc_host *host)
{
	int err, i, funcs;
	u32 ocr, rocr;
	struct mmc_card *card;

	WARN_ON(!host->claimed);

	err = mmc_send_io_op_cond(host, 0, &ocr);
	if (err)
		return err;

	mmc_attach_bus(host, &mmc_sdio_ops);
	if (host->ocr_avail_sdio)
		host->ocr_avail = host->ocr_avail_sdio;


	rocr = mmc_select_voltage(host, ocr);

	/*
	 * Can we support the voltage(s) of the card(s)?
	 */
	if (!rocr) {
		err = -EINVAL;
		goto err;
	}

	/*
	 * Detect and init the card.
	 */
	err = mmc_sdio_init_card(host, rocr, NULL);
	if (err)
		goto err;

	card = host->card;

	/*
	 * Enable runtime PM only if supported by host+card+board
	 */
	if (host->caps & MMC_CAP_POWER_OFF_CARD) {
		/*
		 * Do not allow runtime suspend until after SDIO function
		 * devices are added.
		 */
		pm_runtime_get_noresume(&card->dev);

		/*
		 * Let runtime PM core know our card is active
		 */
		err = pm_runtime_set_active(&card->dev);
		if (err)
			goto remove;

		/*
		 * Enable runtime PM for this card
		 */
		pm_runtime_enable(&card->dev);
	}

	/*
	 * The number of functions on the card is encoded inside
	 * the ocr.
	 */
	funcs = (ocr & 0x70000000) >> 28;
	card->sdio_funcs = 0;

	/*
	 * Initialize (but don't add) all present functions.
	 */
	for (i = 0; i < funcs; i++, card->sdio_funcs++) {
		err = sdio_init_func(host->card, i + 1);
		if (err)
			goto remove;

		/*
		 * Enable Runtime PM for this func (if supported)
		 */
		if (host->caps & MMC_CAP_POWER_OFF_CARD)
			pm_runtime_enable(&card->sdio_func[i]->dev);
	}

	/*
	 * First add the card to the driver model...
	 */
	mmc_release_host(host);
	err = mmc_add_card(host->card);
	if (err)
		goto remove_added;

	/*
	 * ...then the SDIO functions.
	 */
	for (i = 0;i < funcs;i++) {
		err = sdio_add_func(host->card->sdio_func[i]);
		if (err)
			goto remove_added;
	}

	if (host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runtime_put(&card->dev);

	mmc_claim_host(host);
	return 0;


remove:
	mmc_release_host(host);
remove_added:
	/*
	 * The devices are being deleted so it is not necessary to disable
	 * runtime PM. Similarly we also don't pm_runtime_put() the SDIO card
	 * because it needs to be active to remove any function devices that
	 * were probed, and after that it gets deleted.
	 */
	mmc_sdio_remove(host);
	mmc_claim_host(host);
err:
	mmc_detach_bus(host);

	pr_err("%s: error %d whilst initialising SDIO card\n",
		mmc_hostname(host), err);

	return err;
}