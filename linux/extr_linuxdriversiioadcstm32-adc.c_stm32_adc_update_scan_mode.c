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
struct stm32_adc {int /*<<< orphan*/  num_conv; } ;
struct iio_dev {int /*<<< orphan*/  masklength; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_weight (unsigned long const*,int /*<<< orphan*/ ) ; 
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 int stm32_adc_conf_scan_seq (struct iio_dev*,unsigned long const*) ; 

__attribute__((used)) static int stm32_adc_update_scan_mode(struct iio_dev *indio_dev,
				      const unsigned long *scan_mask)
{
	struct stm32_adc *adc = iio_priv(indio_dev);
	int ret;

	adc->num_conv = bitmap_weight(scan_mask, indio_dev->masklength);

	ret = stm32_adc_conf_scan_seq(indio_dev, scan_mask);
	if (ret)
		return ret;

	return 0;
}