#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct lcd_device {int dummy; } ;
struct hx8357_data {int reset; int use_im_pins; int* im_pins; struct spi_device* spi; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int HX8357_NUM_IM_PINS ; 
 scalar_t__ IS_ERR (struct lcd_device*) ; 
 int PTR_ERR (struct lcd_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int devm_gpio_request_one (TYPE_1__*,int,int /*<<< orphan*/ ,char*) ; 
 struct hx8357_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct lcd_device* devm_lcd_device_register (TYPE_1__*,char*,TYPE_1__*,struct hx8357_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  hx8357_dt_ids ; 
 int /*<<< orphan*/  hx8357_lcd_reset (struct lcd_device*) ; 
 int /*<<< orphan*/  hx8357_ops ; 
 scalar_t__ of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* of_get_named_gpio (int /*<<< orphan*/ ,char*,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct lcd_device*) ; 
 int spi_setup (struct spi_device*) ; 
 int stub1 (struct lcd_device*) ; 

__attribute__((used)) static int hx8357_probe(struct spi_device *spi)
{
	struct lcd_device *lcdev;
	struct hx8357_data *lcd;
	const struct of_device_id *match;
	int i, ret;

	lcd = devm_kzalloc(&spi->dev, sizeof(*lcd), GFP_KERNEL);
	if (!lcd)
		return -ENOMEM;

	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(&spi->dev, "SPI setup failed.\n");
		return ret;
	}

	lcd->spi = spi;

	match = of_match_device(hx8357_dt_ids, &spi->dev);
	if (!match || !match->data)
		return -EINVAL;

	lcd->reset = of_get_named_gpio(spi->dev.of_node, "gpios-reset", 0);
	if (!gpio_is_valid(lcd->reset)) {
		dev_err(&spi->dev, "Missing dt property: gpios-reset\n");
		return -EINVAL;
	}

	ret = devm_gpio_request_one(&spi->dev, lcd->reset,
				    GPIOF_OUT_INIT_HIGH,
				    "hx8357-reset");
	if (ret) {
		dev_err(&spi->dev,
			"failed to request gpio %d: %d\n",
			lcd->reset, ret);
		return -EINVAL;
	}

	if (of_find_property(spi->dev.of_node, "im-gpios", NULL)) {
		lcd->use_im_pins = 1;

		for (i = 0; i < HX8357_NUM_IM_PINS; i++) {
			lcd->im_pins[i] = of_get_named_gpio(spi->dev.of_node,
							    "im-gpios", i);
			if (lcd->im_pins[i] == -EPROBE_DEFER) {
				dev_info(&spi->dev, "GPIO requested is not here yet, deferring the probe\n");
				return -EPROBE_DEFER;
			}
			if (!gpio_is_valid(lcd->im_pins[i])) {
				dev_err(&spi->dev, "Missing dt property: im-gpios\n");
				return -EINVAL;
			}

			ret = devm_gpio_request_one(&spi->dev, lcd->im_pins[i],
						    GPIOF_OUT_INIT_LOW,
						    "im_pins");
			if (ret) {
				dev_err(&spi->dev, "failed to request gpio %d: %d\n",
					lcd->im_pins[i], ret);
				return -EINVAL;
			}
		}
	} else {
		lcd->use_im_pins = 0;
	}

	lcdev = devm_lcd_device_register(&spi->dev, "mxsfb", &spi->dev, lcd,
					&hx8357_ops);
	if (IS_ERR(lcdev)) {
		ret = PTR_ERR(lcdev);
		return ret;
	}
	spi_set_drvdata(spi, lcdev);

	hx8357_lcd_reset(lcdev);

	ret = ((int (*)(struct lcd_device *))match->data)(lcdev);
	if (ret) {
		dev_err(&spi->dev, "Couldn't initialize panel\n");
		return ret;
	}

	dev_info(&spi->dev, "Panel probed\n");

	return 0;
}