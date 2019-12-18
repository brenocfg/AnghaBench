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
struct device {struct max8903_pdata* platform_data; } ;
struct platform_device {struct device dev; } ;
struct max8903_pdata {int dok; int dcm; int uok; int cen; int chg; int flt; int usus; scalar_t__ usb_valid; scalar_t__ dc_valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct max8903_data {int fault; int ta_in; int usb_in; TYPE_1__ psy_desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_gpio_request (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_get_value (int) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 struct max8903_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int max8903_setup_gpios(struct platform_device *pdev)
{
	struct max8903_data *data = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	struct max8903_pdata *pdata = pdev->dev.platform_data;
	int ret = 0;
	int gpio;
	int ta_in = 0;
	int usb_in = 0;

	if (pdata->dc_valid) {
		if (gpio_is_valid(pdata->dok)) {
			ret = devm_gpio_request(dev, pdata->dok,
						data->psy_desc.name);
			if (ret) {
				dev_err(dev,
					"Failed GPIO request for dok: %d err %d\n",
					pdata->dok, ret);
				return ret;
			}

			gpio = pdata->dok; /* PULL_UPed Interrupt */
			ta_in = gpio_get_value(gpio) ? 0 : 1;
		} else {
			dev_err(dev, "When DC is wired, DOK should be wired as well.\n");
			return -EINVAL;
		}
	}

	if (gpio_is_valid(pdata->dcm)) {
		ret = devm_gpio_request(dev, pdata->dcm, data->psy_desc.name);
		if (ret) {
			dev_err(dev,
				"Failed GPIO request for dcm: %d err %d\n",
				pdata->dcm, ret);
			return ret;
		}

		gpio = pdata->dcm; /* Output */
		gpio_set_value(gpio, ta_in);
	}

	if (pdata->usb_valid) {
		if (gpio_is_valid(pdata->uok)) {
			ret = devm_gpio_request(dev, pdata->uok,
						data->psy_desc.name);
			if (ret) {
				dev_err(dev,
					"Failed GPIO request for uok: %d err %d\n",
					pdata->uok, ret);
				return ret;
			}

			gpio = pdata->uok;
			usb_in = gpio_get_value(gpio) ? 0 : 1;
		} else {
			dev_err(dev, "When USB is wired, UOK should be wired."
					"as well.\n");
			return -EINVAL;
		}
	}

	if (gpio_is_valid(pdata->cen)) {
		ret = devm_gpio_request(dev, pdata->cen, data->psy_desc.name);
		if (ret) {
			dev_err(dev,
				"Failed GPIO request for cen: %d err %d\n",
				pdata->cen, ret);
			return ret;
		}

		gpio_set_value(pdata->cen, (ta_in || usb_in) ? 0 : 1);
	}

	if (gpio_is_valid(pdata->chg)) {
		ret = devm_gpio_request(dev, pdata->chg, data->psy_desc.name);
		if (ret) {
			dev_err(dev,
				"Failed GPIO request for chg: %d err %d\n",
				pdata->chg, ret);
			return ret;
		}
	}

	if (gpio_is_valid(pdata->flt)) {
		ret = devm_gpio_request(dev, pdata->flt, data->psy_desc.name);
		if (ret) {
			dev_err(dev,
				"Failed GPIO request for flt: %d err %d\n",
				pdata->flt, ret);
			return ret;
		}
	}

	if (gpio_is_valid(pdata->usus)) {
		ret = devm_gpio_request(dev, pdata->usus, data->psy_desc.name);
		if (ret) {
			dev_err(dev,
				"Failed GPIO request for usus: %d err %d\n",
				pdata->usus, ret);
			return ret;
		}
	}

	data->fault = false;
	data->ta_in = ta_in;
	data->usb_in = usb_in;

	return 0;
}