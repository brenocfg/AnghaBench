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
union evm_time {int* bytes; int /*<<< orphan*/  value; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM355EVM_MSP_RTC_0 ; 
 int /*<<< orphan*/  DM355EVM_MSP_RTC_1 ; 
 int /*<<< orphan*/  DM355EVM_MSP_RTC_2 ; 
 int /*<<< orphan*/  DM355EVM_MSP_RTC_3 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int dm355evm_msp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int dm355evm_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	union evm_time	time;
	int		status;
	int		tries = 0;

	do {
		/*
		 * Read LSB(0) to MSB(3) bytes.  Defend against the counter
		 * rolling over by re-reading until the value is stable,
		 * and assuming the four reads take at most a few seconds.
		 */
		status = dm355evm_msp_read(DM355EVM_MSP_RTC_0);
		if (status < 0)
			return status;
		if (tries && time.bytes[0] == status)
			break;
		time.bytes[0] = status;

		status = dm355evm_msp_read(DM355EVM_MSP_RTC_1);
		if (status < 0)
			return status;
		if (tries && time.bytes[1] == status)
			break;
		time.bytes[1] = status;

		status = dm355evm_msp_read(DM355EVM_MSP_RTC_2);
		if (status < 0)
			return status;
		if (tries && time.bytes[2] == status)
			break;
		time.bytes[2] = status;

		status = dm355evm_msp_read(DM355EVM_MSP_RTC_3);
		if (status < 0)
			return status;
		if (tries && time.bytes[3] == status)
			break;
		time.bytes[3] = status;

	} while (++tries < 5);

	dev_dbg(dev, "read timestamp %08x\n", time.value);

	rtc_time64_to_tm(le32_to_cpu(time.value), tm);
	return 0;
}