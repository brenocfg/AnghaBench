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
typedef  scalar_t__ u16 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ FIRMWARE_READY ; 
 int btmrvl_sdio_read_fw_status (struct btmrvl_sdio_card*,scalar_t__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmrvl_sdio_verify_fw_download(struct btmrvl_sdio_card *card,
								int pollnum)
{
	u16 firmwarestat;
	int tries, ret;

	 /* Wait for firmware to become ready */
	for (tries = 0; tries < pollnum; tries++) {
		sdio_claim_host(card->func);
		ret = btmrvl_sdio_read_fw_status(card, &firmwarestat);
		sdio_release_host(card->func);
		if (ret < 0)
			continue;

		if (firmwarestat == FIRMWARE_READY)
			return 0;

		msleep(100);
	}

	return -ETIMEDOUT;
}