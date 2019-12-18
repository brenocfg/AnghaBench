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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct led_pwm_priv {int dummy; } ;
struct led_pwm_platform_data {int num_leds; int /*<<< orphan*/ * leds; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct led_pwm_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int device_get_child_node_count (int /*<<< orphan*/ *) ; 
 struct led_pwm_priv* devm_kzalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int led_pwm_add (int /*<<< orphan*/ *,struct led_pwm_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int led_pwm_create_fwnode (int /*<<< orphan*/ *,struct led_pwm_priv*) ; 
 int /*<<< orphan*/  leds ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct led_pwm_priv*) ; 
 int /*<<< orphan*/  struct_size (struct led_pwm_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int led_pwm_probe(struct platform_device *pdev)
{
	struct led_pwm_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct led_pwm_priv *priv;
	int count, i;
	int ret = 0;

	if (pdata)
		count = pdata->num_leds;
	else
		count = device_get_child_node_count(&pdev->dev);

	if (!count)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev, struct_size(priv, leds, count),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	if (pdata) {
		for (i = 0; i < count; i++) {
			ret = led_pwm_add(&pdev->dev, priv, &pdata->leds[i],
					  NULL);
			if (ret)
				break;
		}
	} else {
		ret = led_pwm_create_fwnode(&pdev->dev, priv);
	}

	if (ret)
		return ret;

	platform_set_drvdata(pdev, priv);

	return 0;
}