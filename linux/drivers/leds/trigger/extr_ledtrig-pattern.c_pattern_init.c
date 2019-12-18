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
typedef  int /*<<< orphan*/  u32 ;
struct led_classdev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * led_get_default_pattern (struct led_classdev*,unsigned int*) ; 
 int pattern_trig_store_patterns (struct led_classdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static void pattern_init(struct led_classdev *led_cdev)
{
	unsigned int size = 0;
	u32 *pattern;
	int err;

	pattern = led_get_default_pattern(led_cdev, &size);
	if (!pattern)
		return;

	if (size % 2) {
		dev_warn(led_cdev->dev, "Expected pattern of tuples\n");
		goto out;
	}

	err = pattern_trig_store_patterns(led_cdev, NULL, pattern, size, false);
	if (err < 0)
		dev_warn(led_cdev->dev,
			 "Pattern initialization failed with error %d\n", err);

out:
	kfree(pattern);
}