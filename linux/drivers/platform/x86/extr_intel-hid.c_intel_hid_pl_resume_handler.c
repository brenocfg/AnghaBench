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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_button_array_enable (struct device*,int) ; 
 int /*<<< orphan*/  intel_hid_pm_complete (struct device*) ; 
 int /*<<< orphan*/  intel_hid_set_enable (struct device*,int) ; 
 int /*<<< orphan*/  pm_suspend_no_platform () ; 

__attribute__((used)) static int intel_hid_pl_resume_handler(struct device *device)
{
	intel_hid_pm_complete(device);

	if (!pm_suspend_no_platform())
		intel_hid_set_enable(device, true);

	intel_button_array_enable(device, true);
	return 0;
}