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
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ debug ; 
 int /*<<< orphan*/  intel_chipset_set_brightness (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int intel_chipset_send_intensity(struct backlight_device *bd)
{
	int intensity = bd->props.brightness;

	if (debug)
		pr_debug("setting brightness to %d\n", intensity);

	intel_chipset_set_brightness(intensity);
	return 0;
}