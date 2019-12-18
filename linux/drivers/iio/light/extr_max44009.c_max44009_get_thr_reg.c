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
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_DIR_FALLING 129 
#define  IIO_EV_DIR_RISING 128 
 int MAX44009_REG_LOWER_THR ; 
 int MAX44009_REG_UPPER_THR ; 

__attribute__((used)) static int max44009_get_thr_reg(enum iio_event_direction dir)
{
	switch (dir) {
	case IIO_EV_DIR_RISING:
		return MAX44009_REG_UPPER_THR;
	case IIO_EV_DIR_FALLING:
		return MAX44009_REG_LOWER_THR;
	default:
		return -EINVAL;
	}
}