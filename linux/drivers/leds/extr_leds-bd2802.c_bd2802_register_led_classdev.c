#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set_blocking; void* brightness; } ;
struct bd2802_led {TYPE_2__ cdev_led1r; TYPE_2__ cdev_led1g; TYPE_2__ cdev_led1b; TYPE_2__ cdev_led2r; TYPE_2__ cdev_led2g; TYPE_2__ cdev_led2b; TYPE_1__* client; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 void* LED_OFF ; 
 int /*<<< orphan*/  bd2802_set_led1b_blink ; 
 int /*<<< orphan*/  bd2802_set_led1b_brightness ; 
 int /*<<< orphan*/  bd2802_set_led1g_blink ; 
 int /*<<< orphan*/  bd2802_set_led1g_brightness ; 
 int /*<<< orphan*/  bd2802_set_led1r_blink ; 
 int /*<<< orphan*/  bd2802_set_led1r_brightness ; 
 int /*<<< orphan*/  bd2802_set_led2b_blink ; 
 int /*<<< orphan*/  bd2802_set_led2b_brightness ; 
 int /*<<< orphan*/  bd2802_set_led2g_blink ; 
 int /*<<< orphan*/  bd2802_set_led2g_brightness ; 
 int /*<<< orphan*/  bd2802_set_led2r_blink ; 
 int /*<<< orphan*/  bd2802_set_led2r_brightness ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_2__*) ; 

__attribute__((used)) static int bd2802_register_led_classdev(struct bd2802_led *led)
{
	int ret;

	led->cdev_led1r.name = "led1_R";
	led->cdev_led1r.brightness = LED_OFF;
	led->cdev_led1r.brightness_set_blocking = bd2802_set_led1r_brightness;
	led->cdev_led1r.blink_set = bd2802_set_led1r_blink;

	ret = led_classdev_register(&led->client->dev, &led->cdev_led1r);
	if (ret < 0) {
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led1r.name);
		goto failed_unregister_led1_R;
	}

	led->cdev_led1g.name = "led1_G";
	led->cdev_led1g.brightness = LED_OFF;
	led->cdev_led1g.brightness_set_blocking = bd2802_set_led1g_brightness;
	led->cdev_led1g.blink_set = bd2802_set_led1g_blink;

	ret = led_classdev_register(&led->client->dev, &led->cdev_led1g);
	if (ret < 0) {
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led1g.name);
		goto failed_unregister_led1_G;
	}

	led->cdev_led1b.name = "led1_B";
	led->cdev_led1b.brightness = LED_OFF;
	led->cdev_led1b.brightness_set_blocking = bd2802_set_led1b_brightness;
	led->cdev_led1b.blink_set = bd2802_set_led1b_blink;

	ret = led_classdev_register(&led->client->dev, &led->cdev_led1b);
	if (ret < 0) {
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led1b.name);
		goto failed_unregister_led1_B;
	}

	led->cdev_led2r.name = "led2_R";
	led->cdev_led2r.brightness = LED_OFF;
	led->cdev_led2r.brightness_set_blocking = bd2802_set_led2r_brightness;
	led->cdev_led2r.blink_set = bd2802_set_led2r_blink;

	ret = led_classdev_register(&led->client->dev, &led->cdev_led2r);
	if (ret < 0) {
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led2r.name);
		goto failed_unregister_led2_R;
	}

	led->cdev_led2g.name = "led2_G";
	led->cdev_led2g.brightness = LED_OFF;
	led->cdev_led2g.brightness_set_blocking = bd2802_set_led2g_brightness;
	led->cdev_led2g.blink_set = bd2802_set_led2g_blink;

	ret = led_classdev_register(&led->client->dev, &led->cdev_led2g);
	if (ret < 0) {
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led2g.name);
		goto failed_unregister_led2_G;
	}

	led->cdev_led2b.name = "led2_B";
	led->cdev_led2b.brightness = LED_OFF;
	led->cdev_led2b.brightness_set_blocking = bd2802_set_led2b_brightness;
	led->cdev_led2b.blink_set = bd2802_set_led2b_blink;
	led->cdev_led2b.flags |= LED_CORE_SUSPENDRESUME;

	ret = led_classdev_register(&led->client->dev, &led->cdev_led2b);
	if (ret < 0) {
		dev_err(&led->client->dev, "couldn't register LED %s\n",
							led->cdev_led2b.name);
		goto failed_unregister_led2_B;
	}

	return 0;

failed_unregister_led2_B:
	led_classdev_unregister(&led->cdev_led2g);
failed_unregister_led2_G:
	led_classdev_unregister(&led->cdev_led2r);
failed_unregister_led2_R:
	led_classdev_unregister(&led->cdev_led1b);
failed_unregister_led1_B:
	led_classdev_unregister(&led->cdev_led1g);
failed_unregister_led1_G:
	led_classdev_unregister(&led->cdev_led1r);
failed_unregister_led1_R:

	return ret;
}