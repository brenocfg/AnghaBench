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
typedef  int u64 ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
typedef  unsigned char hw_counter ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_RTC ; 
 int AB3100_RTC_CLOCK_RATE ; 
 int /*<<< orphan*/  AB3100_TI0 ; 
 int /*<<< orphan*/  AB3100_TI1 ; 
 int /*<<< orphan*/  AB3100_TI2 ; 
 int /*<<< orphan*/  AB3100_TI3 ; 
 int /*<<< orphan*/  AB3100_TI4 ; 
 int /*<<< orphan*/  AB3100_TI5 ; 
 int abx500_mask_and_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int abx500_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int ab3100_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	u8 regs[] = {AB3100_TI0, AB3100_TI1, AB3100_TI2,
		     AB3100_TI3, AB3100_TI4, AB3100_TI5};
	unsigned char buf[6];
	u64 hw_counter = rtc_tm_to_time64(tm) * AB3100_RTC_CLOCK_RATE * 2;
	int err = 0;
	int i;

	buf[0] = (hw_counter) & 0xFF;
	buf[1] = (hw_counter >> 8) & 0xFF;
	buf[2] = (hw_counter >> 16) & 0xFF;
	buf[3] = (hw_counter >> 24) & 0xFF;
	buf[4] = (hw_counter >> 32) & 0xFF;
	buf[5] = (hw_counter >> 40) & 0xFF;

	for (i = 0; i < 6; i++) {
		err = abx500_set_register_interruptible(dev, 0,
							regs[i], buf[i]);
		if (err)
			return err;
	}

	/* Set the flag to mark that the clock is now set */
	return abx500_mask_and_set_register_interruptible(dev, 0,
							  AB3100_RTC,
							  0x01, 0x01);

}