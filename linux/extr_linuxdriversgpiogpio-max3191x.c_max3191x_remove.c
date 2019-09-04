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
struct max3191x_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct max3191x_chip* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int max3191x_remove(struct spi_device *spi)
{
	struct max3191x_chip *max3191x = spi_get_drvdata(spi);

	gpiochip_remove(&max3191x->gpio);
	mutex_destroy(&max3191x->lock);

	return 0;
}