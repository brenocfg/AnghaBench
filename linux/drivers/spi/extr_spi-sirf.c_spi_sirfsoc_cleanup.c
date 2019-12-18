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
struct spi_device {int /*<<< orphan*/  cs_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ spi_get_ctldata (struct spi_device*) ; 

__attribute__((used)) static void spi_sirfsoc_cleanup(struct spi_device *spi)
{
	if (spi_get_ctldata(spi)) {
		gpio_free(spi->cs_gpio);
		kfree(spi_get_ctldata(spi));
	}
}