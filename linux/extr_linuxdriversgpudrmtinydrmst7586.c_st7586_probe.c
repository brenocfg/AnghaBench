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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct spi_device {struct device dev; } ;
struct mipi_dbi {int swap_bytes; int /*<<< orphan*/  tinydrm; int /*<<< orphan*/ * read_commands; struct gpio_desc* reset; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mipi_dbi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_tinydrm_register (int /*<<< orphan*/ *) ; 
 int mipi_dbi_spi_init (struct spi_device*,struct mipi_dbi*,struct gpio_desc*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct mipi_dbi*) ; 
 int /*<<< orphan*/  st7586_driver ; 
 int st7586_init (struct device*,struct mipi_dbi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st7586_mode ; 
 int /*<<< orphan*/  st7586_pipe_funcs ; 

__attribute__((used)) static int st7586_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct mipi_dbi *mipi;
	struct gpio_desc *a0;
	u32 rotation = 0;
	int ret;

	mipi = devm_kzalloc(dev, sizeof(*mipi), GFP_KERNEL);
	if (!mipi)
		return -ENOMEM;

	mipi->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(mipi->reset)) {
		DRM_DEV_ERROR(dev, "Failed to get gpio 'reset'\n");
		return PTR_ERR(mipi->reset);
	}

	a0 = devm_gpiod_get(dev, "a0", GPIOD_OUT_LOW);
	if (IS_ERR(a0)) {
		DRM_DEV_ERROR(dev, "Failed to get gpio 'a0'\n");
		return PTR_ERR(a0);
	}

	device_property_read_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, mipi, a0);
	if (ret)
		return ret;

	/* Cannot read from this controller via SPI */
	mipi->read_commands = NULL;

	/*
	 * we are using 8-bit data, so we are not actually swapping anything,
	 * but setting mipi->swap_bytes makes mipi_dbi_typec3_command() do the
	 * right thing and not use 16-bit transfers (which results in swapped
	 * bytes on little-endian systems and causes out of order data to be
	 * sent to the display).
	 */
	mipi->swap_bytes = true;

	ret = st7586_init(&spi->dev, mipi, &st7586_pipe_funcs, &st7586_driver,
			  &st7586_mode, rotation);
	if (ret)
		return ret;

	spi_set_drvdata(spi, mipi);

	return devm_tinydrm_register(&mipi->tinydrm);
}