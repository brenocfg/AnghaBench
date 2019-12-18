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
struct timespec64 {int dummy; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_BOOTTIME 134 
#define  CLOCK_MONOTONIC 133 
#define  CLOCK_MONOTONIC_COARSE 132 
#define  CLOCK_MONOTONIC_RAW 131 
#define  CLOCK_REALTIME 130 
#define  CLOCK_REALTIME_COARSE 129 
#define  CLOCK_TAI 128 
 int iio_device_get_clock (struct iio_dev const*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  ktime_get_clocktai_ns () ; 
 int /*<<< orphan*/  ktime_get_coarse_real () ; 
 int /*<<< orphan*/  ktime_get_coarse_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  ktime_get_raw_ns () ; 
 int /*<<< orphan*/  ktime_get_real_ns () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec64_to_ns (struct timespec64*) ; 

s64 iio_get_time_ns(const struct iio_dev *indio_dev)
{
	struct timespec64 tp;

	switch (iio_device_get_clock(indio_dev)) {
	case CLOCK_REALTIME:
		return ktime_get_real_ns();
	case CLOCK_MONOTONIC:
		return ktime_get_ns();
	case CLOCK_MONOTONIC_RAW:
		return ktime_get_raw_ns();
	case CLOCK_REALTIME_COARSE:
		return ktime_to_ns(ktime_get_coarse_real());
	case CLOCK_MONOTONIC_COARSE:
		ktime_get_coarse_ts64(&tp);
		return timespec64_to_ns(&tp);
	case CLOCK_BOOTTIME:
		return ktime_get_boottime_ns();
	case CLOCK_TAI:
		return ktime_get_clocktai_ns();
	default:
		BUG();
	}
}