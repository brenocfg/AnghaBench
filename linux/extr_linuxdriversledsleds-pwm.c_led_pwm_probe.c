#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct led_pwm_priv {int dummy; } ;
struct led_pwm_platform_data {int num_leds; int /*<<< orphan*/ * leds; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct led_pwm_platform_data* dev_get_platdata (TYPE_1__*) ; 
 struct led_pwm_priv* devm_kzalloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int led_pwm_add (TYPE_1__*,struct led_pwm_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_pwm_cleanup (struct led_pwm_priv*) ; 
 int led_pwm_create_of (TYPE_1__*,struct led_pwm_priv*) ; 
 int of_get_child_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct led_pwm_priv*) ; 
 int /*<<< orphan*/  sizeof_pwm_leds_priv (int) ; 

__attribute__((used)) static int led_pwm_probe(struct platform_device *pdev)
{
	struct led_pwm_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct led_pwm_priv *priv;
	int count, i;
	int ret = 0;

	if (pdata)
		count = pdata->num_leds;
	else
		count = of_get_child_count(pdev->dev.of_node);

	if (!count)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev, sizeof_pwm_leds_priv(count),
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
		ret = led_pwm_create_of(&pdev->dev, priv);
	}

	if (ret) {
		led_pwm_cleanup(priv);
		return ret;
	}

	platform_set_drvdata(pdev, priv);

	return 0;
}