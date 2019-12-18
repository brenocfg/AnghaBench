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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SD_CFG3 ; 
 int STATUS_SUCCESS ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

__attribute__((used)) static int sd_dummy_clock(struct rtsx_chip *chip)
{
	int retval;

	retval = rtsx_write_register(chip, REG_SD_CFG3, 0x01, 0x01);
	if (retval)
		return retval;
	wait_timeout(5);
	retval = rtsx_write_register(chip, REG_SD_CFG3, 0x01, 0);
	if (retval)
		return retval;

	return STATUS_SUCCESS;
}