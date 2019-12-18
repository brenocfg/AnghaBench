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
struct ps8622_bridge {int /*<<< orphan*/  client; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int brightness; scalar_t__ power; int state; } ;
struct backlight_device {TYPE_1__ props; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 int BL_CORE_SUSPENDED ; 
 int EINVAL ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 struct ps8622_bridge* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int ps8622_set (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int ps8622_backlight_update(struct backlight_device *bl)
{
	struct ps8622_bridge *ps8622 = dev_get_drvdata(&bl->dev);
	int ret, brightness = bl->props.brightness;

	if (bl->props.power != FB_BLANK_UNBLANK ||
	    bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	if (!ps8622->enabled)
		return -EINVAL;

	ret = ps8622_set(ps8622->client, 0x01, 0xa7, brightness);

	return ret;
}