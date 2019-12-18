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
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* backlight_map ; 
 int msi_wmi_query_block (int,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int bl_get(struct backlight_device *bd)
{
	int level, err, ret;

	/* Instance 1 is "get backlight", cmp with DSDT */
	err = msi_wmi_query_block(1, &ret);
	if (err) {
		pr_err("Could not query backlight: %d\n", err);
		return -EINVAL;
	}
	pr_debug("Get: Query block returned: %d\n", ret);
	for (level = 0; level < ARRAY_SIZE(backlight_map); level++) {
		if (backlight_map[level] == ret) {
			pr_debug("Current backlight level: 0x%X - index: %d\n",
				 backlight_map[level], level);
			break;
		}
	}
	if (level == ARRAY_SIZE(backlight_map)) {
		pr_err("get: Invalid brightness value: 0x%X\n", ret);
		return -EINVAL;
	}
	return level;
}