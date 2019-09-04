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
typedef  scalar_t__ u8 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  func; scalar_t__ helper; TYPE_1__* reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_fw_status0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int MAX_POLL_TRIES ; 
 scalar_t__ btmrvl_sdio_download_fw_w_helper (struct btmrvl_sdio_card*) ; 
 int btmrvl_sdio_download_helper (struct btmrvl_sdio_card*) ; 
 scalar_t__ btmrvl_sdio_verify_fw_download (struct btmrvl_sdio_card*,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 scalar_t__ sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmrvl_sdio_download_fw(struct btmrvl_sdio_card *card)
{
	int ret;
	u8 fws0;
	int pollnum = MAX_POLL_TRIES;

	if (!card || !card->func) {
		BT_ERR("card or function is NULL!");
		return -EINVAL;
	}

	if (!btmrvl_sdio_verify_fw_download(card, 1)) {
		BT_DBG("Firmware already downloaded!");
		return 0;
	}

	sdio_claim_host(card->func);

	/* Check if other function driver is downloading the firmware */
	fws0 = sdio_readb(card->func, card->reg->card_fw_status0, &ret);
	if (ret) {
		BT_ERR("Failed to read FW downloading status!");
		ret = -EIO;
		goto done;
	}
	if (fws0) {
		BT_DBG("BT not the winner (%#x). Skip FW downloading", fws0);

		/* Give other function more time to download the firmware */
		pollnum *= 10;
	} else {
		if (card->helper) {
			ret = btmrvl_sdio_download_helper(card);
			if (ret) {
				BT_ERR("Failed to download helper!");
				ret = -EIO;
				goto done;
			}
		}

		if (btmrvl_sdio_download_fw_w_helper(card)) {
			BT_ERR("Failed to download firmware!");
			ret = -EIO;
			goto done;
		}
	}

	/*
	 * winner or not, with this test the FW synchronizes when the
	 * module can continue its initialization
	 */
	if (btmrvl_sdio_verify_fw_download(card, pollnum)) {
		BT_ERR("FW failed to be active in time!");
		ret = -ETIMEDOUT;
		goto done;
	}

	sdio_release_host(card->func);

	return 0;

done:
	sdio_release_host(card->func);
	return ret;
}