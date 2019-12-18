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
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;
struct aat2870_bl_driver_data {struct backlight_device* bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct aat2870_bl_driver_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int aat2870_bl_remove(struct platform_device *pdev)
{
	struct aat2870_bl_driver_data *aat2870_bl = platform_get_drvdata(pdev);
	struct backlight_device *bd = aat2870_bl->bd;

	bd->props.power = FB_BLANK_POWERDOWN;
	bd->props.brightness = 0;
	backlight_update_status(bd);

	return 0;
}