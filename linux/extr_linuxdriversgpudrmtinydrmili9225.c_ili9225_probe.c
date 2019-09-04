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
struct mipi_dbi {int /*<<< orphan*/  tinydrm; int /*<<< orphan*/  command; struct gpio_desc* reset; } ;
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
 int /*<<< orphan*/  ili9225_dbi_command ; 
 int /*<<< orphan*/  ili9225_driver ; 
 int ili9225_init (struct device*,struct mipi_dbi*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ili9225_mode ; 
 int /*<<< orphan*/  ili9225_pipe_funcs ; 
 int mipi_dbi_spi_init (struct spi_device*,struct mipi_dbi*,struct gpio_desc*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct mipi_dbi*) ; 

__attribute__((used)) static int ili9225_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct mipi_dbi *mipi;
	struct gpio_desc *rs;
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

	rs = devm_gpiod_get(dev, "rs", GPIOD_OUT_LOW);
	if (IS_ERR(rs)) {
		DRM_DEV_ERROR(dev, "Failed to get gpio 'rs'\n");
		return PTR_ERR(rs);
	}

	device_property_read_u32(dev, "rotation", &rotation);

	ret = mipi_dbi_spi_init(spi, mipi, rs);
	if (ret)
		return ret;

	/* override the command function set in  mipi_dbi_spi_init() */
	mipi->command = ili9225_dbi_command;

	ret = ili9225_init(&spi->dev, mipi, &ili9225_pipe_funcs,
			   &ili9225_driver, &ili9225_mode, rotation);
	if (ret)
		return ret;

	spi_set_drvdata(spi, mipi);

	return devm_tinydrm_register(&mipi->tinydrm);
}