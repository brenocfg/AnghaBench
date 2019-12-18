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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/ * devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * led_port ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raq_power_off_led ; 
 int /*<<< orphan*/  raq_web_led ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int cobalt_raq_led_probe(struct platform_device *pdev)
{
	struct resource *res;
	int retval;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EBUSY;

	led_port = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (!led_port)
		return -ENOMEM;

	retval = led_classdev_register(&pdev->dev, &raq_power_off_led);
	if (retval)
		goto err_null;

	retval = led_classdev_register(&pdev->dev, &raq_web_led);
	if (retval)
		goto err_unregister;

	return 0;

err_unregister:
	led_classdev_unregister(&raq_power_off_led);

err_null:
	led_port = NULL;

	return retval;
}