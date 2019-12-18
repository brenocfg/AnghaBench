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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ stm32_dfsdm_get_jextsel (struct iio_dev*,struct iio_trigger*) ; 

__attribute__((used)) static int stm32_dfsdm_validate_trigger(struct iio_dev *indio_dev,
					struct iio_trigger *trig)
{
	return stm32_dfsdm_get_jextsel(indio_dev, trig) < 0 ? -EINVAL : 0;
}