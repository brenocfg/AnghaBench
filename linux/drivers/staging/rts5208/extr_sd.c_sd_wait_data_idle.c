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
 int SD_DATA_IDLE ; 
 int /*<<< orphan*/  SD_DATA_STATE ; 
 int STATUS_SUCCESS ; 
 int STATUS_TIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sd_wait_data_idle(struct rtsx_chip *chip)
{
	int retval = STATUS_TIMEDOUT;
	int i;
	u8 val = 0;

	for (i = 0; i < 100; i++) {
		retval = rtsx_read_register(chip, SD_DATA_STATE, &val);
		if (retval)
			return retval;
		if (val & SD_DATA_IDLE) {
			retval = STATUS_SUCCESS;
			break;
		}
		udelay(100);
	}
	dev_dbg(rtsx_dev(chip), "SD_DATA_STATE: 0x%02x\n", val);

	return retval;
}