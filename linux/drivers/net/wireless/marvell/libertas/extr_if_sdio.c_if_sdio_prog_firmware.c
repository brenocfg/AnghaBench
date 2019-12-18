#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct if_sdio_card {scalar_t__ model; TYPE_1__* func; int /*<<< orphan*/  priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IF_SDIO_FIRMWARE_OK ; 
 int /*<<< orphan*/  IF_SDIO_H_INT_MASK ; 
 scalar_t__ MODEL_8686 ; 
 int /*<<< orphan*/  fw_table ; 
 int /*<<< orphan*/  if_sdio_do_prog_firmware ; 
 int /*<<< orphan*/  if_sdio_finish_power_on (struct if_sdio_card*) ; 
 int if_sdio_read_scratch (struct if_sdio_card*,int*) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*,...) ; 
 int lbs_get_firmware_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_1__*) ; 
 int /*<<< orphan*/  sdio_writeb (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int if_sdio_prog_firmware(struct if_sdio_card *card)
{
	int ret;
	u16 scratch;

	/*
	 * Disable interrupts
	 */
	sdio_claim_host(card->func);
	sdio_writeb(card->func, 0x00, IF_SDIO_H_INT_MASK, &ret);
	sdio_release_host(card->func);

	sdio_claim_host(card->func);
	scratch = if_sdio_read_scratch(card, &ret);
	sdio_release_host(card->func);

	lbs_deb_sdio("firmware status = %#x\n", scratch);
	lbs_deb_sdio("scratch ret = %d\n", ret);

	if (ret)
		goto out;


	/*
	 * The manual clearly describes that FEDC is the right code to use
	 * to detect firmware presence, but for SD8686 it is not that simple.
	 * Scratch is also used to store the RX packet length, so we lose
	 * the FEDC value early on. So we use a non-zero check in order
	 * to validate firmware presence.
	 * Additionally, the SD8686 in the Gumstix always has the high scratch
	 * bit set, even when the firmware is not loaded. So we have to
	 * exclude that from the test.
	 */
	if (scratch == IF_SDIO_FIRMWARE_OK) {
		lbs_deb_sdio("firmware already loaded\n");
		if_sdio_finish_power_on(card);
		return 0;
	} else if ((card->model == MODEL_8686) && (scratch & 0x7fff)) {
		lbs_deb_sdio("firmware may be running\n");
		if_sdio_finish_power_on(card);
		return 0;
	}

	ret = lbs_get_firmware_async(card->priv, &card->func->dev, card->model,
				     fw_table, if_sdio_do_prog_firmware);

out:
	return ret;
}