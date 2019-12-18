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
struct pisosr_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer; int /*<<< orphan*/  spi; scalar_t__ load_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pisosr_gpio_refresh(struct pisosr_gpio *gpio)
{
	int ret;

	mutex_lock(&gpio->lock);

	if (gpio->load_gpio) {
		gpiod_set_value_cansleep(gpio->load_gpio, 1);
		udelay(1); /* registers load time (~10ns) */
		gpiod_set_value_cansleep(gpio->load_gpio, 0);
		udelay(1); /* registers recovery time (~5ns) */
	}

	ret = spi_read(gpio->spi, gpio->buffer, gpio->buffer_size);

	mutex_unlock(&gpio->lock);

	return ret;
}