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
typedef  int u32 ;
typedef  int /*<<< orphan*/  TW_Device_Extension ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TW_STATUS_REG_ADDR (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ twa_check_bits (int) ; 
 int /*<<< orphan*/  twa_decode_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int twa_poll_status_gone(TW_Device_Extension *tw_dev, u32 flag, int seconds)
{
	u32 status_reg_value;
	unsigned long before;
	int retval = 1;

	status_reg_value = readl(TW_STATUS_REG_ADDR(tw_dev));
	before = jiffies;

	if (twa_check_bits(status_reg_value))
		twa_decode_bits(tw_dev, status_reg_value);

	while ((status_reg_value & flag) != 0) {
		status_reg_value = readl(TW_STATUS_REG_ADDR(tw_dev));
		if (twa_check_bits(status_reg_value))
			twa_decode_bits(tw_dev, status_reg_value);

		if (time_after(jiffies, before + HZ * seconds))
			goto out;

		msleep(50);
	}
	retval = 0;
out:
	return retval;
}