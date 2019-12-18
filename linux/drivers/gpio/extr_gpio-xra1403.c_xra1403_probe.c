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
struct TYPE_2__ {int ngpio; char* label; int base; int can_sleep; int /*<<< orphan*/  owner; int /*<<< orphan*/ * parent; int /*<<< orphan*/  dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; } ;
struct xra1403 {TYPE_1__ chip; struct gpio_desc* regmap; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ *,TYPE_1__*,struct xra1403*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct xra1403* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct xra1403*) ; 
 int /*<<< orphan*/  xra1403_dbg_show ; 
 int /*<<< orphan*/  xra1403_direction_input ; 
 int /*<<< orphan*/  xra1403_direction_output ; 
 int /*<<< orphan*/  xra1403_get ; 
 int /*<<< orphan*/  xra1403_get_direction ; 
 int /*<<< orphan*/  xra1403_regmap_cfg ; 
 int /*<<< orphan*/  xra1403_set ; 

__attribute__((used)) static int xra1403_probe(struct spi_device *spi)
{
	struct xra1403 *xra;
	struct gpio_desc *reset_gpio;
	int ret;

	xra = devm_kzalloc(&spi->dev, sizeof(*xra), GFP_KERNEL);
	if (!xra)
		return -ENOMEM;

	/* bring the chip out of reset if reset pin is provided*/
	reset_gpio = devm_gpiod_get_optional(&spi->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(reset_gpio))
		dev_warn(&spi->dev, "Could not get reset-gpios\n");

	xra->chip.direction_input = xra1403_direction_input;
	xra->chip.direction_output = xra1403_direction_output;
	xra->chip.get_direction = xra1403_get_direction;
	xra->chip.get = xra1403_get;
	xra->chip.set = xra1403_set;

	xra->chip.dbg_show = xra1403_dbg_show;

	xra->chip.ngpio = 16;
	xra->chip.label = "xra1403";

	xra->chip.base = -1;
	xra->chip.can_sleep = true;
	xra->chip.parent = &spi->dev;
	xra->chip.owner = THIS_MODULE;

	xra->regmap = devm_regmap_init_spi(spi, &xra1403_regmap_cfg);
	if (IS_ERR(xra->regmap)) {
		ret = PTR_ERR(xra->regmap);
		dev_err(&spi->dev, "Failed to allocate regmap: %d\n", ret);
		return ret;
	}

	ret = devm_gpiochip_add_data(&spi->dev, &xra->chip, xra);
	if (ret < 0) {
		dev_err(&spi->dev, "Unable to register gpiochip\n");
		return ret;
	}

	spi_set_drvdata(spi, xra);

	return 0;
}