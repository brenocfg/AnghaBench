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
typedef  scalar_t__ u8 ;
struct rtsx_chip {int phy_voltage; scalar_t__ asic_code; } ;

/* Variables and functions */
 scalar_t__ SD_IO_1V8 ; 
 scalar_t__ SD_IO_3V3 ; 
 int /*<<< orphan*/  SD_IO_USING_1V8 ; 
 int /*<<< orphan*/  SD_PAD_CTL ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int rtsx_write_phy_register (struct rtsx_chip*,int,int) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_change_bank_voltage(struct rtsx_chip *chip, u8 voltage)
{
	int retval;

	if (voltage == SD_IO_3V3) {
		if (chip->asic_code) {
			retval = rtsx_write_phy_register(chip, 0x08,
							 0x4FC0 |
							 chip->phy_voltage);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		} else {
			retval = rtsx_write_register(chip, SD_PAD_CTL,
						     SD_IO_USING_1V8, 0);
			if (retval)
				return retval;
		}
	} else if (voltage == SD_IO_1V8) {
		if (chip->asic_code) {
			retval = rtsx_write_phy_register(chip, 0x08,
							 0x4C40 |
							 chip->phy_voltage);
			if (retval != STATUS_SUCCESS)
				return STATUS_FAIL;
		} else {
			retval = rtsx_write_register(chip, SD_PAD_CTL,
						     SD_IO_USING_1V8,
						     SD_IO_USING_1V8);
			if (retval)
				return retval;
		}
	} else {
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}