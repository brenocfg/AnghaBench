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
struct mlxreg_led_priv_data {TYPE_1__* pdev; struct mlxreg_core_platform_data* pdata; } ;
struct led_classdev {int brightness; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  (* brightness_set_blocking ) (struct led_classdev*,int) ;int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  name; } ;
struct mlxreg_led_data {struct mlxreg_core_data* data; int /*<<< orphan*/  led_cdev_name; int /*<<< orphan*/  base_color; struct mlxreg_led_priv_data* data_parent; struct led_classdev led_cdev; } ;
struct mlxreg_core_platform_data {int counter; struct mlxreg_core_data* data; } ;
struct mlxreg_core_data {char* label; int /*<<< orphan*/  reg; int /*<<< orphan*/  mask; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int LED_OFF ; 
 int /*<<< orphan*/  LED_ON ; 
 int /*<<< orphan*/  MLXREG_LED_AMBER_SOLID ; 
 int /*<<< orphan*/  MLXREG_LED_GREEN_SOLID ; 
 int /*<<< orphan*/  MLXREG_LED_RED_SOLID ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxreg_led_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 
 int /*<<< orphan*/  mlxreg_led_blink_set ; 
 int /*<<< orphan*/  mlxreg_led_brightness_get ; 
 int /*<<< orphan*/  mlxreg_led_brightness_set (struct led_classdev*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int mlxreg_led_config(struct mlxreg_led_priv_data *priv)
{
	struct mlxreg_core_platform_data *led_pdata = priv->pdata;
	struct mlxreg_core_data *data = led_pdata->data;
	struct mlxreg_led_data *led_data;
	struct led_classdev *led_cdev;
	enum led_brightness brightness;
	int i;
	int err;

	for (i = 0; i < led_pdata->counter; i++, data++) {
		led_data = devm_kzalloc(&priv->pdev->dev, sizeof(*led_data),
					GFP_KERNEL);
		if (!led_data)
			return -ENOMEM;

		led_cdev = &led_data->led_cdev;
		led_data->data_parent = priv;
		if (strstr(data->label, "red") ||
		    strstr(data->label, "orange")) {
			brightness = LED_OFF;
			led_data->base_color = MLXREG_LED_RED_SOLID;
		} else if (strstr(data->label, "amber")) {
			brightness = LED_OFF;
			led_data->base_color = MLXREG_LED_AMBER_SOLID;
		} else {
			brightness = LED_OFF;
			led_data->base_color = MLXREG_LED_GREEN_SOLID;
		}
		sprintf(led_data->led_cdev_name, "%s:%s", "mlxreg",
			data->label);
		led_cdev->name = led_data->led_cdev_name;
		led_cdev->brightness = brightness;
		led_cdev->max_brightness = LED_ON;
		led_cdev->brightness_set_blocking =
						mlxreg_led_brightness_set;
		led_cdev->brightness_get = mlxreg_led_brightness_get;
		led_cdev->blink_set = mlxreg_led_blink_set;
		led_cdev->flags = LED_CORE_SUSPENDRESUME;
		led_data->data = data;
		err = devm_led_classdev_register(&priv->pdev->dev, led_cdev);
		if (err)
			return err;

		if (led_cdev->brightness)
			mlxreg_led_brightness_set(led_cdev,
						  led_cdev->brightness);
		dev_info(led_cdev->dev, "label: %s, mask: 0x%02x, offset:0x%02x\n",
			 data->label, data->mask, data->reg);
	}

	return 0;
}