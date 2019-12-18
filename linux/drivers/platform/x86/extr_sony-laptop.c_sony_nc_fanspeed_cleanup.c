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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fan_handle ; 
 int /*<<< orphan*/ * hsf_handle ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sony_nc_fanspeed_cleanup(struct platform_device *pd)
{
	if (fan_handle) {
		device_remove_file(&pd->dev, fan_handle);
		kfree(fan_handle);
		fan_handle = NULL;
	}
	if (hsf_handle) {
		device_remove_file(&pd->dev, hsf_handle);
		kfree(hsf_handle);
		hsf_handle = NULL;
	}
}