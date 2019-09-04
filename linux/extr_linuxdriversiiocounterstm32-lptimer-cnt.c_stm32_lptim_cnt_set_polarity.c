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
struct stm32_lptim_cnt {unsigned int polarity; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct stm32_lptim_cnt* iio_priv (struct iio_dev*) ; 
 scalar_t__ stm32_lptim_is_enabled (struct stm32_lptim_cnt*) ; 

__attribute__((used)) static int stm32_lptim_cnt_set_polarity(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan,
					unsigned int type)
{
	struct stm32_lptim_cnt *priv = iio_priv(indio_dev);

	if (stm32_lptim_is_enabled(priv))
		return -EBUSY;

	priv->polarity = type;

	return 0;
}