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
struct exynos_adc {unsigned int regs; } ;

/* Variables and functions */
 int EINVAL ; 
 struct exynos_adc* iio_priv (struct iio_dev*) ; 
 unsigned int readl (unsigned int) ; 

__attribute__((used)) static int exynos_adc_reg_access(struct iio_dev *indio_dev,
			      unsigned reg, unsigned writeval,
			      unsigned *readval)
{
	struct exynos_adc *info = iio_priv(indio_dev);

	if (readval == NULL)
		return -EINVAL;

	*readval = readl(info->regs + reg);

	return 0;
}