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
struct TYPE_2__ {scalar_t__ fb_blank; scalar_t__ power; } ;
struct backlight_device {TYPE_1__ props; int /*<<< orphan*/  dev; } ;
struct acx565akm_panel {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ FB_BLANK_UNBLANK ; 
 unsigned int acx565akm_get_actual_brightness (struct acx565akm_panel*) ; 
 struct acx565akm_panel* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acx565akm_bl_get_intensity(struct backlight_device *dev)
{
	struct acx565akm_panel *lcd = dev_get_drvdata(&dev->dev);
	unsigned int intensity;

	mutex_lock(&lcd->mutex);

	if (dev->props.fb_blank == FB_BLANK_UNBLANK &&
	    dev->props.power == FB_BLANK_UNBLANK)
		intensity = acx565akm_get_actual_brightness(lcd);
	else
		intensity = 0;

	mutex_unlock(&lcd->mutex);

	return intensity;
}