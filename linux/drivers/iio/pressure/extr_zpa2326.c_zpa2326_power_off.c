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
 int /*<<< orphan*/  zpa2326_dbg (struct iio_dev const*,char*) ; 

__attribute__((used)) static void zpa2326_power_off(const struct iio_dev         *indio_dev,
			      const struct zpa2326_private *private)
{
	regulator_disable(private->vdd);
	regulator_disable(private->vref);

	zpa2326_dbg(indio_dev, "powered off");
}