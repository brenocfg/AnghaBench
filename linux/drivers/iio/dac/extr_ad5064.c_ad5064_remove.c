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
struct device {int dummy; } ;
struct ad5064_state {int /*<<< orphan*/  vref_reg; int /*<<< orphan*/  use_internal_vref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad5064_num_vref (struct ad5064_state*) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad5064_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5064_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct ad5064_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	if (!st->use_internal_vref)
		regulator_bulk_disable(ad5064_num_vref(st), st->vref_reg);

	return 0;
}