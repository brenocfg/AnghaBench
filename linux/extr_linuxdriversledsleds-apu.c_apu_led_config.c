#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct led_classdev {int max_brightness; int /*<<< orphan*/  (* brightness_set ) (struct led_classdev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  brightness; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct apu_led_priv {struct led_classdev cdev; TYPE_1__ param; } ;
struct apu_led_pdata {int dummy; } ;
struct TYPE_6__ {int num_led_instances; scalar_t__ platform; struct apu_led_priv* pled; TYPE_2__* profile; int /*<<< orphan*/  iosize; } ;
struct TYPE_5__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  offset; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ APU1_LED_PLATFORM ; 
 scalar_t__ APU2_LED_PLATFORM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  apu1_led_brightness_set (struct led_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apu2_led_brightness_set (struct led_classdev*,int /*<<< orphan*/ ) ; 
 TYPE_3__* apu_led ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct apu_led_priv* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (struct device*,struct led_classdev*) ; 
 int /*<<< orphan*/  led_classdev_unregister (struct led_classdev*) ; 
 int /*<<< orphan*/  stub1 (struct led_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apu_led_config(struct device *dev, struct apu_led_pdata *apuld)
{
	int i;
	int err;

	apu_led->pled = devm_kcalloc(dev,
		apu_led->num_led_instances, sizeof(struct apu_led_priv),
		GFP_KERNEL);

	if (!apu_led->pled)
		return -ENOMEM;

	for (i = 0; i < apu_led->num_led_instances; i++) {
		struct apu_led_priv *pled = &apu_led->pled[i];
		struct led_classdev *led_cdev = &pled->cdev;

		led_cdev->name = apu_led->profile[i].name;
		led_cdev->brightness = apu_led->profile[i].brightness;
		led_cdev->max_brightness = 1;
		led_cdev->flags = LED_CORE_SUSPENDRESUME;
		if (apu_led->platform == APU1_LED_PLATFORM)
			led_cdev->brightness_set = apu1_led_brightness_set;
		else if (apu_led->platform == APU2_LED_PLATFORM)
			led_cdev->brightness_set = apu2_led_brightness_set;

		pled->param.addr = devm_ioremap(dev,
				apu_led->profile[i].offset, apu_led->iosize);
		if (!pled->param.addr) {
			err = -ENOMEM;
			goto error;
		}

		err = led_classdev_register(dev, led_cdev);
		if (err)
			goto error;

		led_cdev->brightness_set(led_cdev, apu_led->profile[i].brightness);
	}

	return 0;

error:
	while (i-- > 0)
		led_classdev_unregister(&apu_led->pled[i].cdev);

	return err;
}