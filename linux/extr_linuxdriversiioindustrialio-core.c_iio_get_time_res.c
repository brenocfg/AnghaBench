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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_BOOTTIME 134 
#define  CLOCK_MONOTONIC 133 
#define  CLOCK_MONOTONIC_COARSE 132 
#define  CLOCK_MONOTONIC_RAW 131 
#define  CLOCK_REALTIME 130 
#define  CLOCK_REALTIME_COARSE 129 
#define  CLOCK_TAI 128 
 unsigned int LOW_RES_NSEC ; 
 unsigned int hrtimer_resolution ; 
 int iio_device_get_clock (struct iio_dev const*) ; 

unsigned int iio_get_time_res(const struct iio_dev *indio_dev)
{
	switch (iio_device_get_clock(indio_dev)) {
	case CLOCK_REALTIME:
	case CLOCK_MONOTONIC:
	case CLOCK_MONOTONIC_RAW:
	case CLOCK_BOOTTIME:
	case CLOCK_TAI:
		return hrtimer_resolution;
	case CLOCK_REALTIME_COARSE:
	case CLOCK_MONOTONIC_COARSE:
		return LOW_RES_NSEC;
	default:
		BUG();
	}
}