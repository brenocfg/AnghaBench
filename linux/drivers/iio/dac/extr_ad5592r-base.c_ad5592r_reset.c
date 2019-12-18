#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct gpio_desc {int dummy; } ;
struct ad5592r_state {TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reg_write ) (struct ad5592r_state*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AD5592R_REG_RESET ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (struct gpio_desc*,int) ; 
 struct iio_dev* iio_priv_to_dev (struct ad5592r_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ad5592r_reset(struct ad5592r_state *st)
{
	struct gpio_desc *gpio;
	struct iio_dev *iio_dev = iio_priv_to_dev(st);

	gpio = devm_gpiod_get_optional(st->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	if (gpio) {
		udelay(1);
		gpiod_set_value(gpio, 1);
	} else {
		mutex_lock(&iio_dev->mlock);
		/* Writing this magic value resets the device */
		st->ops->reg_write(st, AD5592R_REG_RESET, 0xdac);
		mutex_unlock(&iio_dev->mlock);
	}

	udelay(250);

	return 0;
}