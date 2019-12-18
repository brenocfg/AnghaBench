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

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_LEVEL_ADDR ; 
 int BACKLIGHT_LEVEL_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_backlight_level(int level)
{
	if (level < 0 || level > BACKLIGHT_LEVEL_MAX)
		return -EINVAL;

	ec_write(BACKLIGHT_LEVEL_ADDR, level);

	return 0;
}