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
struct stm32_adc {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct stm32_adc* iio_priv (struct iio_dev*) ; 
 unsigned int stm32_adc_readl (struct stm32_adc*,unsigned int) ; 
 int /*<<< orphan*/  stm32_adc_writel (struct stm32_adc*,unsigned int,unsigned int) ; 

__attribute__((used)) static int stm32_adc_debugfs_reg_access(struct iio_dev *indio_dev,
					unsigned reg, unsigned writeval,
					unsigned *readval)
{
	struct stm32_adc *adc = iio_priv(indio_dev);

	if (!readval)
		stm32_adc_writel(adc, reg, writeval);
	else
		*readval = stm32_adc_readl(adc, reg);

	return 0;
}