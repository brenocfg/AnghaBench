#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; } ;
struct spi_device {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ngpio; struct device* parent; } ;
struct pisosr_gpio {int buffer_size; TYPE_1__ chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  load_gpio; void* buffer; struct spi_device* spi; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct pisosr_gpio*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u16 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct pisosr_gpio*) ; 
 TYPE_1__ template_chip ; 

__attribute__((used)) static int pisosr_gpio_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct pisosr_gpio *gpio;
	int ret;

	gpio = devm_kzalloc(dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	spi_set_drvdata(spi, gpio);

	gpio->chip = template_chip;
	gpio->chip.parent = dev;
	of_property_read_u16(dev->of_node, "ngpios", &gpio->chip.ngpio);

	gpio->spi = spi;

	gpio->buffer_size = DIV_ROUND_UP(gpio->chip.ngpio, 8);
	gpio->buffer = devm_kzalloc(dev, gpio->buffer_size, GFP_KERNEL);
	if (!gpio->buffer)
		return -ENOMEM;

	gpio->load_gpio = devm_gpiod_get_optional(dev, "load", GPIOD_OUT_LOW);
	if (IS_ERR(gpio->load_gpio)) {
		ret = PTR_ERR(gpio->load_gpio);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Unable to allocate load GPIO\n");
		return ret;
	}

	mutex_init(&gpio->lock);

	ret = gpiochip_add_data(&gpio->chip, gpio);
	if (ret < 0) {
		dev_err(dev, "Unable to register gpiochip\n");
		return ret;
	}

	return 0;
}