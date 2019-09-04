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
struct adp5520_leds_platform_data {int num_leds; } ;
struct adp5520_led {int /*<<< orphan*/  cdev; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int ADP5520_LED1_EN ; 
 int ADP5520_LED2_EN ; 
 int ADP5520_LED3_EN ; 
 int /*<<< orphan*/  ADP5520_LED_CONTROL ; 
 int /*<<< orphan*/  adp5520_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adp5520_leds_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct adp5520_led* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int adp5520_led_remove(struct platform_device *pdev)
{
	struct adp5520_leds_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct adp5520_led *led;
	int i;

	led = platform_get_drvdata(pdev);

	adp5520_clr_bits(led->master, ADP5520_LED_CONTROL,
		 ADP5520_LED1_EN | ADP5520_LED2_EN | ADP5520_LED3_EN);

	for (i = 0; i < pdata->num_leds; i++) {
		led_classdev_unregister(&led[i].cdev);
	}

	return 0;
}