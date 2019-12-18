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
struct ns2_led_priv {int num_leds; int /*<<< orphan*/ * leds_data; } ;
struct ns2_led_platform_data {int num_leds; int /*<<< orphan*/ * leds; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int create_ns2_led (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_ns2_led (int /*<<< orphan*/ *) ; 
 struct ns2_led_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ns2_leds_get_of_pdata (int /*<<< orphan*/ *,struct ns2_led_platform_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ns2_led_priv*) ; 
 int sizeof_ns2_led_priv (int) ; 

__attribute__((used)) static int ns2_led_probe(struct platform_device *pdev)
{
	struct ns2_led_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct ns2_led_priv *priv;
	int i;
	int ret;

#ifdef CONFIG_OF_GPIO
	if (!pdata) {
		pdata = devm_kzalloc(&pdev->dev,
				     sizeof(struct ns2_led_platform_data),
				     GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;

		ret = ns2_leds_get_of_pdata(&pdev->dev, pdata);
		if (ret)
			return ret;
	}
#else
	if (!pdata)
		return -EINVAL;
#endif /* CONFIG_OF_GPIO */

	priv = devm_kzalloc(&pdev->dev,
			    sizeof_ns2_led_priv(pdata->num_leds), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->num_leds = pdata->num_leds;

	for (i = 0; i < priv->num_leds; i++) {
		ret = create_ns2_led(pdev, &priv->leds_data[i],
				     &pdata->leds[i]);
		if (ret < 0) {
			for (i = i - 1; i >= 0; i--)
				delete_ns2_led(&priv->leds_data[i]);
			return ret;
		}
	}

	platform_set_drvdata(pdev, priv);

	return 0;
}