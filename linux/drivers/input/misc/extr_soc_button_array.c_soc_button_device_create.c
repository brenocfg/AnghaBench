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
struct soc_button_info {int autorepeat; int /*<<< orphan*/  wakeup; scalar_t__ name; int /*<<< orphan*/  event_code; int /*<<< orphan*/  event_type; int /*<<< orphan*/  acpi_index; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpio_keys_platform_data {int nbuttons; int rep; struct gpio_keys_button* buttons; } ;
struct gpio_keys_button {int gpio; int active_low; int debounce_interval; int /*<<< orphan*/  wakeup; scalar_t__ desc; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR_OR_ZERO (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct gpio_keys_platform_data*) ; 
 struct gpio_keys_platform_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 struct platform_device* platform_device_register_resndata (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gpio_keys_platform_data*,int) ; 
 int soc_button_lookup_gpio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct platform_device *
soc_button_device_create(struct platform_device *pdev,
			 const struct soc_button_info *button_info,
			 bool autorepeat)
{
	const struct soc_button_info *info;
	struct platform_device *pd;
	struct gpio_keys_button *gpio_keys;
	struct gpio_keys_platform_data *gpio_keys_pdata;
	int n_buttons = 0;
	int gpio;
	int error;

	for (info = button_info; info->name; info++)
		if (info->autorepeat == autorepeat)
			n_buttons++;

	gpio_keys_pdata = devm_kzalloc(&pdev->dev,
				       sizeof(*gpio_keys_pdata) +
					sizeof(*gpio_keys) * n_buttons,
				       GFP_KERNEL);
	if (!gpio_keys_pdata)
		return ERR_PTR(-ENOMEM);

	gpio_keys = (void *)(gpio_keys_pdata + 1);
	n_buttons = 0;

	for (info = button_info; info->name; info++) {
		if (info->autorepeat != autorepeat)
			continue;

		gpio = soc_button_lookup_gpio(&pdev->dev, info->acpi_index);
		if (!gpio_is_valid(gpio)) {
			/*
			 * Skip GPIO if not present. Note we deliberately
			 * ignore -EPROBE_DEFER errors here. On some devices
			 * Intel is using so called virtual GPIOs which are not
			 * GPIOs at all but some way for AML code to check some
			 * random status bits without need a custom opregion.
			 * In some cases the resources table we parse points to
			 * such a virtual GPIO, since these are not real GPIOs
			 * we do not have a driver for these so they will never
			 * show up, therefore we ignore -EPROBE_DEFER.
			 */
			continue;
		}

		gpio_keys[n_buttons].type = info->event_type;
		gpio_keys[n_buttons].code = info->event_code;
		gpio_keys[n_buttons].gpio = gpio;
		gpio_keys[n_buttons].active_low = 1;
		gpio_keys[n_buttons].desc = info->name;
		gpio_keys[n_buttons].wakeup = info->wakeup;
		/* These devices often use cheap buttons, use 50 ms debounce */
		gpio_keys[n_buttons].debounce_interval = 50;
		n_buttons++;
	}

	if (n_buttons == 0) {
		error = -ENODEV;
		goto err_free_mem;
	}

	gpio_keys_pdata->buttons = gpio_keys;
	gpio_keys_pdata->nbuttons = n_buttons;
	gpio_keys_pdata->rep = autorepeat;

	pd = platform_device_register_resndata(&pdev->dev, "gpio-keys",
					       PLATFORM_DEVID_AUTO, NULL, 0,
					       gpio_keys_pdata,
					       sizeof(*gpio_keys_pdata));
	error = PTR_ERR_OR_ZERO(pd);
	if (error) {
		dev_err(&pdev->dev,
			"failed registering gpio-keys: %d\n", error);
		goto err_free_mem;
	}

	return pd;

err_free_mem:
	devm_kfree(&pdev->dev, gpio_keys_pdata);
	return ERR_PTR(error);
}