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
struct spi_byte_led {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct spi_byte_led* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int spi_byte_remove(struct spi_device *spi)
{
	struct spi_byte_led	*led = spi_get_drvdata(spi);

	mutex_destroy(&led->mutex);

	return 0;
}