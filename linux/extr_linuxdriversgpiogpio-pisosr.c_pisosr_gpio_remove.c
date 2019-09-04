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
struct spi_device {int dummy; } ;
struct pisosr_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct pisosr_gpio* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int pisosr_gpio_remove(struct spi_device *spi)
{
	struct pisosr_gpio *gpio = spi_get_drvdata(spi);

	gpiochip_remove(&gpio->chip);

	mutex_destroy(&gpio->lock);

	return 0;
}