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
typedef  int u8 ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OT_EC_BL_BRIGHTNESS_ADDRESS ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int get_backlight_brightness(struct backlight_device *b)
{
	u8 value;
	ec_read(OT_EC_BL_BRIGHTNESS_ADDRESS, &value);

	return value;
}