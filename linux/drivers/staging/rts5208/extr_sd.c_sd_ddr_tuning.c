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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_chip {int sd_ctl; scalar_t__ sd_ddr_tx_phase; } ;

/* Variables and functions */
 int SD_DDR_TX_PHASE_SET_BY_USER ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  TUNE_TX ; 
 int sd_change_phase (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_ddr_pre_tuning_tx (struct rtsx_chip*) ; 
 int sd_tuning_rx (struct rtsx_chip*) ; 
 int sd_tuning_tx (struct rtsx_chip*) ; 

__attribute__((used)) static int sd_ddr_tuning(struct rtsx_chip *chip)
{
	int retval;

	if (!(chip->sd_ctl & SD_DDR_TX_PHASE_SET_BY_USER)) {
		retval = sd_ddr_pre_tuning_tx(chip);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	} else {
		retval = sd_change_phase(chip, (u8)chip->sd_ddr_tx_phase,
					 TUNE_TX);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	}

	retval = sd_tuning_rx(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (!(chip->sd_ctl & SD_DDR_TX_PHASE_SET_BY_USER)) {
		retval = sd_tuning_tx(chip);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}