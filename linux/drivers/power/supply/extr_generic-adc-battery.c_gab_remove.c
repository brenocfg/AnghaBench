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
struct platform_device {int dummy; } ;
struct gab_platform_data {int /*<<< orphan*/  gpio_charge_finished; } ;
struct TYPE_2__ {int /*<<< orphan*/  properties; } ;
struct gab {int /*<<< orphan*/  bat_work; TYPE_1__ psy_desc; scalar_t__* channel; int /*<<< orphan*/  psy; struct gab_platform_data* pdata; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gab*) ; 
 int /*<<< orphan*/  gab_chan_name ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_channel_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct gab* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gab_remove(struct platform_device *pdev)
{
	int chan;
	struct gab *adc_bat = platform_get_drvdata(pdev);
	struct gab_platform_data *pdata = adc_bat->pdata;

	power_supply_unregister(adc_bat->psy);

	if (gpio_is_valid(pdata->gpio_charge_finished)) {
		free_irq(gpio_to_irq(pdata->gpio_charge_finished), adc_bat);
		gpio_free(pdata->gpio_charge_finished);
	}

	for (chan = 0; chan < ARRAY_SIZE(gab_chan_name); chan++) {
		if (adc_bat->channel[chan])
			iio_channel_release(adc_bat->channel[chan]);
	}

	kfree(adc_bat->psy_desc.properties);
	cancel_delayed_work(&adc_bat->bat_work);
	return 0;
}