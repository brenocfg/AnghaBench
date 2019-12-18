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
 int /*<<< orphan*/  EFUSE_CTRL ; 
 int /*<<< orphan*/  EFUSE_DATA ; 
 int STATUS_SUCCESS ; 
 int STATUS_TIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

int rtsx_write_efuse(struct rtsx_chip *chip, u8 addr, u8 val)
{
	int retval;
	int i, j;
	u8 data = 0, tmp = 0xFF;

	for (i = 0; i < 8; i++) {
		if (val & (u8)(1 << i))
			continue;

		tmp &= (~(u8)(1 << i));
		dev_dbg(rtsx_dev(chip), "Write 0x%x to 0x%x\n", tmp, addr);

		retval = rtsx_write_register(chip, EFUSE_DATA, 0xFF, tmp);
		if (retval)
			return retval;
		retval = rtsx_write_register(chip, EFUSE_CTRL, 0xFF,
					     0xA0 | addr);
		if (retval)
			return retval;

		for (j = 0; j < 100; j++) {
			retval = rtsx_read_register(chip, EFUSE_CTRL, &data);
			if (retval)
				return retval;
			if (!(data & 0x80))
				break;
			wait_timeout(3);
		}

		if (data & 0x80)
			return STATUS_TIMEDOUT;

		wait_timeout(5);
	}

	return STATUS_SUCCESS;
}