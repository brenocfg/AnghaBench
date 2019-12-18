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
typedef  int u8 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SD_STAT1 ; 
 int /*<<< orphan*/  SD_BUSY ; 
 int SD_DAT0_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_check_data0_status(struct rtsx_chip *chip)
{
	int retval;
	u8 stat;

	retval = rtsx_read_register(chip, REG_SD_STAT1, &stat);
	if (retval)
		return retval;

	if (!(stat & SD_DAT0_STATUS)) {
		sd_set_err_code(chip, SD_BUSY);
		return STATUS_FAIL;
	}

	return STATUS_SUCCESS;
}