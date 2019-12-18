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
struct rtsx_chip {int ocp_stat; int /*<<< orphan*/  ft2_fast_mode; scalar_t__ asic_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_OE ; 
 int /*<<< orphan*/  FPGA_PULL_CTL ; 
 int FPGA_SD_PULL_CTL_BIT ; 
 int /*<<< orphan*/  SD_CARD ; 
 int SD_OC_EVER ; 
 int SD_OC_NOW ; 
 int SD_OUTPUT_EN ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int card_power_on (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int enable_card_clock (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int sd_power_off_card3v3 (struct rtsx_chip*) ; 
 int sd_pull_ctl_enable (struct rtsx_chip*) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int sd_init_power(struct rtsx_chip *chip)
{
	int retval;

	retval = sd_power_off_card3v3(chip);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (!chip->ft2_fast_mode)
		wait_timeout(250);

	retval = enable_card_clock(chip, SD_CARD);
	if (retval != STATUS_SUCCESS)
		return STATUS_FAIL;

	if (chip->asic_code) {
		retval = sd_pull_ctl_enable(chip);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;
	} else {
		retval = rtsx_write_register(chip, FPGA_PULL_CTL,
					     FPGA_SD_PULL_CTL_BIT | 0x20, 0);
		if (retval)
			return retval;
	}

	if (!chip->ft2_fast_mode) {
		retval = card_power_on(chip, SD_CARD);
		if (retval != STATUS_SUCCESS)
			return STATUS_FAIL;

		wait_timeout(260);

#ifdef SUPPORT_OCP
		if (chip->ocp_stat & (SD_OC_NOW | SD_OC_EVER)) {
			dev_dbg(rtsx_dev(chip), "Over current, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			return STATUS_FAIL;
		}
#endif
	}

	retval = rtsx_write_register(chip, CARD_OE, SD_OUTPUT_EN,
				     SD_OUTPUT_EN);
	if (retval)
		return retval;

	return STATUS_SUCCESS;
}