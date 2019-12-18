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
union evm_time {int /*<<< orphan*/ * bytes; int /*<<< orphan*/  value; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM355EVM_MSP_RTC_0 ; 
 int /*<<< orphan*/  DM355EVM_MSP_RTC_1 ; 
 int /*<<< orphan*/  DM355EVM_MSP_RTC_2 ; 
 int /*<<< orphan*/  DM355EVM_MSP_RTC_3 ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int dm355evm_msp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int dm355evm_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	union evm_time	time;
	unsigned long	value;
	int		status;

	value = rtc_tm_to_time64(tm);
	time.value = cpu_to_le32(value);

	dev_dbg(dev, "write timestamp %08x\n", time.value);

	/*
	 * REVISIT handle non-atomic writes ... maybe just retry until
	 * byte[1] sticks (no rollover)?
	 */
	status = dm355evm_msp_write(time.bytes[0], DM355EVM_MSP_RTC_0);
	if (status < 0)
		return status;

	status = dm355evm_msp_write(time.bytes[1], DM355EVM_MSP_RTC_1);
	if (status < 0)
		return status;

	status = dm355evm_msp_write(time.bytes[2], DM355EVM_MSP_RTC_2);
	if (status < 0)
		return status;

	status = dm355evm_msp_write(time.bytes[3], DM355EVM_MSP_RTC_3);
	if (status < 0)
		return status;

	return 0;
}