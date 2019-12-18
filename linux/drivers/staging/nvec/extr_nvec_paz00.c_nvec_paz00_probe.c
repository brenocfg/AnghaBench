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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_5__ {char* name; scalar_t__ brightness; int /*<<< orphan*/  flags; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  max_brightness; } ;
struct nvec_led {TYPE_2__ cdev; struct nvec_chip* nvec; } ;
struct nvec_chip {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  NVEC_LED_MAX ; 
 struct nvec_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct nvec_led* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  nvec_led_brightness_set ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nvec_led*) ; 

__attribute__((used)) static int nvec_paz00_probe(struct platform_device *pdev)
{
	struct nvec_chip *nvec = dev_get_drvdata(pdev->dev.parent);
	struct nvec_led *led;
	int ret = 0;

	led = devm_kzalloc(&pdev->dev, sizeof(*led), GFP_KERNEL);
	if (!led)
		return -ENOMEM;

	led->cdev.max_brightness = NVEC_LED_MAX;

	led->cdev.brightness_set = nvec_led_brightness_set;
	led->cdev.name = "paz00-led";
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->nvec = nvec;

	platform_set_drvdata(pdev, led);

	ret = devm_led_classdev_register(&pdev->dev, &led->cdev);
	if (ret < 0)
		return ret;

	/* to expose the default value to userspace */
	led->cdev.brightness = 0;

	return 0;
}