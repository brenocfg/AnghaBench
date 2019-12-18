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
struct stm32_dfsdm_adc {int (* cb ) (void const*,size_t,void*) ;void* cb_priv; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 

int stm32_dfsdm_get_buff_cb(struct iio_dev *iio_dev,
			    int (*cb)(const void *data, size_t size,
				      void *private),
			    void *private)
{
	struct stm32_dfsdm_adc *adc;

	if (!iio_dev)
		return -EINVAL;
	adc = iio_priv(iio_dev);

	adc->cb = cb;
	adc->cb_priv = private;

	return 0;
}