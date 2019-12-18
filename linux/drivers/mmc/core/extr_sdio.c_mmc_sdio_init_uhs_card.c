#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sda_spec3; } ;
struct mmc_card {TYPE_3__* host; TYPE_1__ scr; } ;
struct TYPE_5__ {scalar_t__ timing; } ;
struct TYPE_6__ {TYPE_2__ ios; } ;

/* Variables and functions */
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 scalar_t__ MMC_TIMING_UHS_SDR50 ; 
 int mmc_execute_tuning (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_host_is_spi (TYPE_3__*) ; 
 int sdio_enable_4bit_bus (struct mmc_card*) ; 
 int /*<<< orphan*/  sdio_select_driver_type (struct mmc_card*) ; 
 int sdio_set_bus_speed_mode (struct mmc_card*) ; 

__attribute__((used)) static int mmc_sdio_init_uhs_card(struct mmc_card *card)
{
	int err;

	if (!card->scr.sda_spec3)
		return 0;

	/* Switch to wider bus */
	err = sdio_enable_4bit_bus(card);
	if (err)
		goto out;

	/* Set the driver strength for the card */
	sdio_select_driver_type(card);

	/* Set bus speed mode of the card */
	err = sdio_set_bus_speed_mode(card);
	if (err)
		goto out;

	/*
	 * SPI mode doesn't define CMD19 and tuning is only valid for SDR50 and
	 * SDR104 mode SD-cards. Note that tuning is mandatory for SDR104.
	 */
	if (!mmc_host_is_spi(card->host) &&
	    ((card->host->ios.timing == MMC_TIMING_UHS_SDR50) ||
	      (card->host->ios.timing == MMC_TIMING_UHS_SDR104)))
		err = mmc_execute_tuning(card);
out:
	return err;
}