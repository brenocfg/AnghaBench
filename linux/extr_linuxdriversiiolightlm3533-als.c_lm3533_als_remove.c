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
struct platform_device {int dummy; } ;
struct lm3533_als {scalar_t__ irq; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct lm3533_als* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  lm3533_als_disable (struct lm3533_als*) ; 
 int /*<<< orphan*/  lm3533_als_set_int_mode (struct iio_dev*,int) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int lm3533_als_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct lm3533_als *als = iio_priv(indio_dev);

	lm3533_als_set_int_mode(indio_dev, false);
	iio_device_unregister(indio_dev);
	lm3533_als_disable(als);
	if (als->irq)
		free_irq(als->irq, indio_dev);

	return 0;
}