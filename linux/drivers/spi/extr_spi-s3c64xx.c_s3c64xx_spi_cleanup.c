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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct spi_device {int /*<<< orphan*/  cs_gpio; TYPE_1__ dev; } ;
struct s3c64xx_spi_csinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s3c64xx_spi_csinfo*) ; 
 struct s3c64xx_spi_csinfo* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3c64xx_spi_cleanup(struct spi_device *spi)
{
	struct s3c64xx_spi_csinfo *cs = spi_get_ctldata(spi);

	if (gpio_is_valid(spi->cs_gpio)) {
		gpio_free(spi->cs_gpio);
		if (spi->dev.of_node)
			kfree(cs);
		else {
			/* On non-DT platforms, the SPI core sets
			 * spi->cs_gpio to -ENOENT and .setup()
			 * overrides it with the GPIO pin value
			 * passed using platform data.
			 */
			spi->cs_gpio = -ENOENT;
		}
	}

	spi_set_ctldata(spi, NULL);
}