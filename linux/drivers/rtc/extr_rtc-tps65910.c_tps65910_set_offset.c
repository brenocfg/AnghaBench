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
struct device {int dummy; } ;
typedef  long s64 ;

/* Variables and functions */
 int ERANGE ; 
 long MAX_OFFSET ; 
 long MIN_OFFSET ; 
 long long PPB_MULT ; 
 scalar_t__ TICKS_PER_HOUR ; 
 long div_s64 (long,long long) ; 
 int tps65910_rtc_set_calibration (struct device*,int) ; 

__attribute__((used)) static int tps65910_set_offset(struct device *dev, long offset)
{
	int calibration;
	s64 tmp;
	int ret;

	/* Make sure offset value is within supported range */
	if (offset < MIN_OFFSET || offset > MAX_OFFSET)
		return -ERANGE;

	/* Convert from ppb format to RTC calibration register format */
	tmp = offset * (s64)TICKS_PER_HOUR;
	if (tmp < 0)
		tmp -= PPB_MULT / 2LL;
	else
		tmp += PPB_MULT / 2LL;
	tmp = div_s64(tmp, PPB_MULT);

	/* Offset value operates in negative way, so swap sign */
	calibration = (int)-tmp;

	ret = tps65910_rtc_set_calibration(dev, calibration);

	return ret;
}