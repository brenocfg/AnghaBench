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
struct iio_trigger {int dummy; } ;
struct iio_dev {int modes; } ;

/* Variables and functions */
 int EINVAL ; 
 int INDIO_HARDWARE_TRIGGERED ; 

__attribute__((used)) static int stm32_lptim_validate_device(struct iio_trigger *trig,
				       struct iio_dev *indio_dev)
{
	if (indio_dev->modes & INDIO_HARDWARE_TRIGGERED)
		return 0;

	return -EINVAL;
}