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
struct TYPE_2__ {int sd3_drv_type; int /*<<< orphan*/  uhs_max_dtr; } ;
struct mmc_card {int drive_strength; int /*<<< orphan*/  host; TYPE_1__ sw_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_CCCR_DRIVE_STRENGTH ; 
 unsigned char SDIO_DRIVE_DTSx_MASK ; 
 unsigned char SDIO_DRIVE_DTSx_SHIFT ; 
 int SD_DRIVER_TYPE_B ; 
 unsigned char host_drive_to_sdio_drive (int) ; 
 int mmc_io_rw_direct (struct mmc_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char*) ; 
 int mmc_select_drive_strength (struct mmc_card*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  mmc_set_driver_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdio_select_driver_type(struct mmc_card *card)
{
	int card_drv_type, drive_strength, drv_type;
	unsigned char card_strength;
	int err;

	card->drive_strength = 0;

	card_drv_type = card->sw_caps.sd3_drv_type | SD_DRIVER_TYPE_B;

	drive_strength = mmc_select_drive_strength(card,
						   card->sw_caps.uhs_max_dtr,
						   card_drv_type, &drv_type);

	if (drive_strength) {
		/* if error just use default for drive strength B */
		err = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_DRIVE_STRENGTH, 0,
				       &card_strength);
		if (err)
			return;

		card_strength &= ~(SDIO_DRIVE_DTSx_MASK<<SDIO_DRIVE_DTSx_SHIFT);
		card_strength |= host_drive_to_sdio_drive(drive_strength);

		/* if error default to drive strength B */
		err = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_DRIVE_STRENGTH,
				       card_strength, NULL);
		if (err)
			return;
		card->drive_strength = drive_strength;
	}

	if (drv_type)
		mmc_set_driver_type(card->host, drv_type);
}