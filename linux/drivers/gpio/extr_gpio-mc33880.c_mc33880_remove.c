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
struct mc33880 {int /*<<< orphan*/  lock; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct mc33880* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int mc33880_remove(struct spi_device *spi)
{
	struct mc33880 *mc;

	mc = spi_get_drvdata(spi);
	if (!mc)
		return -ENODEV;

	gpiochip_remove(&mc->chip);
	mutex_destroy(&mc->lock);

	return 0;
}