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
struct TYPE_2__ {int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  name; } ;
struct ims_pcu_backlight {TYPE_1__ cdev; int /*<<< orphan*/  name; } ;
struct ims_pcu {int device_no; int /*<<< orphan*/  dev; struct ims_pcu_backlight backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMS_PCU_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ims_pcu_backlight_get_brightness ; 
 int /*<<< orphan*/  ims_pcu_backlight_set_brightness ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int ims_pcu_setup_backlight(struct ims_pcu *pcu)
{
	struct ims_pcu_backlight *backlight = &pcu->backlight;
	int error;

	snprintf(backlight->name, sizeof(backlight->name),
		 "pcu%d::kbd_backlight", pcu->device_no);

	backlight->cdev.name = backlight->name;
	backlight->cdev.max_brightness = IMS_PCU_MAX_BRIGHTNESS;
	backlight->cdev.brightness_get = ims_pcu_backlight_get_brightness;
	backlight->cdev.brightness_set_blocking =
					 ims_pcu_backlight_set_brightness;

	error = led_classdev_register(pcu->dev, &backlight->cdev);
	if (error) {
		dev_err(pcu->dev,
			"Failed to register backlight LED device, error: %d\n",
			error);
		return error;
	}

	return 0;
}