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
struct rtsx_chip {scalar_t__ asic_code; int /*<<< orphan*/  ft2_fast_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  FPGA_PULL_CTL ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  XD_CARD ; 
 int XD_OUTPUT_EN ; 
 int card_power_off (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int disable_card_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 
 int xd_pull_ctl_disable (struct rtsx_chip*) ; 

int xd_power_off_card3v3(struct rtsx_chip *chip)
{
	int retval;

	retval = disable_card_clock(chip, XD_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	retval = rtsx_write_register(chip, CARD_OE, XD_OUTPUT_EN, 0);
	if (retval)
		return retval;

	if (!chip->ft2_fast_mode) {
		retval = card_power_off(chip, XD_CARD);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		wait_timeout(50);
	}

	if (chip->asic_code) {
		retval = xd_pull_ctl_disable(chip);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	} else {
		retval = rtsx_write_register(chip, FPGA_PULL_CTL, 0xFF, 0xDF);
		if (retval)
			return retval;
	}

	return STATUS_SUCCESS;
}