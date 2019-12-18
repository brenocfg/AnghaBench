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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int max_brightness; int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  brightness; int /*<<< orphan*/  name; } ;
struct dac124s085_led {int id; TYPE_1__ ldev; int /*<<< orphan*/  name; int /*<<< orphan*/  mutex; struct spi_device* spi; } ;
struct dac124s085 {struct dac124s085_led* leds; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dac124s085_led*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  dac124s085_set_brightness ; 
 struct dac124s085* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct dac124s085*) ; 

__attribute__((used)) static int dac124s085_probe(struct spi_device *spi)
{
	struct dac124s085	*dac;
	struct dac124s085_led	*led;
	int i, ret;

	dac = devm_kzalloc(&spi->dev, sizeof(*dac), GFP_KERNEL);
	if (!dac)
		return -ENOMEM;

	spi->bits_per_word = 16;

	for (i = 0; i < ARRAY_SIZE(dac->leds); i++) {
		led		= dac->leds + i;
		led->id		= i;
		led->spi	= spi;
		snprintf(led->name, sizeof(led->name), "dac124s085-%d", i);
		mutex_init(&led->mutex);
		led->ldev.name = led->name;
		led->ldev.brightness = LED_OFF;
		led->ldev.max_brightness = 0xfff;
		led->ldev.brightness_set_blocking = dac124s085_set_brightness;
		ret = led_classdev_register(&spi->dev, &led->ldev);
		if (ret < 0)
			goto eledcr;
	}

	spi_set_drvdata(spi, dac);

	return 0;

eledcr:
	while (i--)
		led_classdev_unregister(&dac->leds[i].ldev);

	return ret;
}