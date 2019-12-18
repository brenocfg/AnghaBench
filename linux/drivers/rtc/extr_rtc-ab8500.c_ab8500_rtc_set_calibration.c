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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int /*<<< orphan*/  AB8500_RTC_CALIB_REG ; 
 int EINVAL ; 
 int abx500_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int ab8500_rtc_set_calibration(struct device *dev, int calibration)
{
	int retval;
	u8  rtccal = 0;

	/*
	 * Check that the calibration value (which is in units of 0.5
	 * parts-per-million) is in the AB8500's range for RtcCalibration
	 * register. -128 (0x80) is not permitted because the AB8500 uses
	 * a sign-bit rather than two's complement, so 0x80 is just another
	 * representation of zero.
	 */
	if ((calibration < -127) || (calibration > 127)) {
		dev_err(dev, "RtcCalibration value outside permitted range\n");
		return -EINVAL;
	}

	/*
	 * The AB8500 uses sign (in bit7) and magnitude (in bits0-7)
	 * so need to convert to this sort of representation before writing
	 * into RtcCalibration register...
	 */
	if (calibration >= 0)
		rtccal = 0x7F & calibration;
	else
		rtccal = ~(calibration - 1) | 0x80;

	retval = abx500_set_register_interruptible(dev, AB8500_RTC,
			AB8500_RTC_CALIB_REG, rtccal);

	return retval;
}