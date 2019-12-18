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
struct ov965x {int /*<<< orphan*/ * gpios; int /*<<< orphan*/  sd; int /*<<< orphan*/  regmap; } ;
struct ov9650_platform_data {int gpio_pwdn; int gpio_reset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 size_t GPIO_PWDN ; 
 size_t GPIO_RST ; 
 int NUM_GPIOS ; 
 int /*<<< orphan*/  debug ; 
 int devm_gpio_request_one (struct device*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_export (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int,int) ; 
 int /*<<< orphan*/  gpio_to_desc (int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int ov965x_configure_gpios_pdata(struct ov965x *ov965x,
				const struct ov9650_platform_data *pdata)
{
	int ret, i;
	int gpios[NUM_GPIOS];
	struct device *dev = regmap_get_device(ov965x->regmap);

	gpios[GPIO_PWDN] = pdata->gpio_pwdn;
	gpios[GPIO_RST]  = pdata->gpio_reset;

	for (i = 0; i < ARRAY_SIZE(ov965x->gpios); i++) {
		int gpio = gpios[i];

		if (!gpio_is_valid(gpio))
			continue;
		ret = devm_gpio_request_one(dev, gpio,
					    GPIOF_OUT_INIT_HIGH, "OV965X");
		if (ret < 0)
			return ret;
		v4l2_dbg(1, debug, &ov965x->sd, "set gpio %d to 1\n", gpio);

		gpio_set_value_cansleep(gpio, 1);
		gpio_export(gpio, 0);
		ov965x->gpios[i] = gpio_to_desc(gpio);
	}

	return 0;
}