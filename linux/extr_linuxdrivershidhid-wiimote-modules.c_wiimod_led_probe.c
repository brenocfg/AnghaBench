#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct wiimote_data {struct led_classdev** leds; TYPE_2__ state; TYPE_1__* hdev; } ;
struct wiimod_ops {size_t arg; } ;
struct led_classdev {char* name; int max_brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  brightness_get; scalar_t__ brightness; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WIIPROTO_FLAG_LED1 ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  kfree (struct led_classdev*) ; 
 struct led_classdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (struct device*,struct led_classdev*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  wiimod_led_get ; 
 int /*<<< orphan*/  wiimod_led_set ; 
 int /*<<< orphan*/  wiiproto_req_leds (struct wiimote_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wiimod_led_probe(const struct wiimod_ops *ops,
			    struct wiimote_data *wdata)
{
	struct device *dev = &wdata->hdev->dev;
	size_t namesz = strlen(dev_name(dev)) + 9;
	struct led_classdev *led;
	unsigned long flags;
	char *name;
	int ret;

	led = kzalloc(sizeof(struct led_classdev) + namesz, GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	name = (void*)&led[1];
	snprintf(name, namesz, "%s:blue:p%lu", dev_name(dev), ops->arg);
	led->name = name;
	led->brightness = 0;
	led->max_brightness = 1;
	led->brightness_get = wiimod_led_get;
	led->brightness_set = wiimod_led_set;

	wdata->leds[ops->arg] = led;
	ret = led_classdev_register(dev, led);
	if (ret)
		goto err_free;

	/* enable LED1 to stop initial LED-blinking */
	if (ops->arg == 0) {
		spin_lock_irqsave(&wdata->state.lock, flags);
		wiiproto_req_leds(wdata, WIIPROTO_FLAG_LED1);
		spin_unlock_irqrestore(&wdata->state.lock, flags);
	}

	return 0;

err_free:
	wdata->leds[ops->arg] = NULL;
	kfree(led);
	return ret;
}