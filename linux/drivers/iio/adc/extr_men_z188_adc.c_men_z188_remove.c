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
struct z188_adc {int /*<<< orphan*/  mem; int /*<<< orphan*/  base; } ;
struct mcb_device {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct z188_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct iio_dev* mcb_get_drvdata (struct mcb_device*) ; 
 int /*<<< orphan*/  mcb_release_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void men_z188_remove(struct mcb_device *dev)
{
	struct iio_dev *indio_dev  = mcb_get_drvdata(dev);
	struct z188_adc *adc = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	iounmap(adc->base);
	mcb_release_mem(adc->mem);
}