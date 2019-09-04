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
struct ad7766 {int /*<<< orphan*/  reg; int /*<<< orphan*/  mclk; int /*<<< orphan*/  pd_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad7766* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7766_postdisable(struct iio_dev *indio_dev)
{
	struct ad7766 *ad7766 = iio_priv(indio_dev);

	gpiod_set_value(ad7766->pd_gpio, 1);

	/*
	 * The PD pin is synchronous to the clock, so give it some time to
	 * notice the change before we disable the clock.
	 */
	msleep(20);

	clk_disable_unprepare(ad7766->mclk);
	regulator_bulk_disable(ARRAY_SIZE(ad7766->reg), ad7766->reg);

	return 0;
}