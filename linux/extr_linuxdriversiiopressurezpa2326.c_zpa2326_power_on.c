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
struct zpa2326_private {int /*<<< orphan*/  vref; int /*<<< orphan*/  vdd; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*) ; 
 int zpa2326_enable_device (struct iio_dev const*) ; 
 int zpa2326_reset_device (struct iio_dev const*) ; 
 int /*<<< orphan*/  zpa2326_sleep (struct iio_dev const*) ; 

__attribute__((used)) static int zpa2326_power_on(const struct iio_dev         *indio_dev,
			    const struct zpa2326_private *private)
{
	int err;

	err = regulator_enable(private->vref);
	if (err)
		return err;

	err = regulator_enable(private->vdd);
	if (err)
		goto vref;

	zpa2326_dbg(indio_dev, "powered on");

	err = zpa2326_enable_device(indio_dev);
	if (err)
		goto vdd;

	err = zpa2326_reset_device(indio_dev);
	if (err)
		goto sleep;

	return 0;

sleep:
	zpa2326_sleep(indio_dev);
vdd:
	regulator_disable(private->vdd);
vref:
	regulator_disable(private->vref);

	zpa2326_dbg(indio_dev, "powered off");

	return err;
}