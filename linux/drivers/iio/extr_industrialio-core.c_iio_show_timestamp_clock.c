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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_BOOTTIME 134 
#define  CLOCK_MONOTONIC 133 
#define  CLOCK_MONOTONIC_COARSE 132 
#define  CLOCK_MONOTONIC_RAW 131 
#define  CLOCK_REALTIME 130 
#define  CLOCK_REALTIME_COARSE 129 
#define  CLOCK_TAI 128 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int iio_device_get_clock (struct iio_dev const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static ssize_t iio_show_timestamp_clock(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	const struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	const clockid_t clk = iio_device_get_clock(indio_dev);
	const char *name;
	ssize_t sz;

	switch (clk) {
	case CLOCK_REALTIME:
		name = "realtime\n";
		sz = sizeof("realtime\n");
		break;
	case CLOCK_MONOTONIC:
		name = "monotonic\n";
		sz = sizeof("monotonic\n");
		break;
	case CLOCK_MONOTONIC_RAW:
		name = "monotonic_raw\n";
		sz = sizeof("monotonic_raw\n");
		break;
	case CLOCK_REALTIME_COARSE:
		name = "realtime_coarse\n";
		sz = sizeof("realtime_coarse\n");
		break;
	case CLOCK_MONOTONIC_COARSE:
		name = "monotonic_coarse\n";
		sz = sizeof("monotonic_coarse\n");
		break;
	case CLOCK_BOOTTIME:
		name = "boottime\n";
		sz = sizeof("boottime\n");
		break;
	case CLOCK_TAI:
		name = "tai\n";
		sz = sizeof("tai\n");
		break;
	default:
		BUG();
	}

	memcpy(buf, name, sz);
	return sz;
}