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
struct hl_device {scalar_t__ pm_mng_profile; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ PM_AUTO ; 
 scalar_t__ PM_MANUAL ; 
 struct hl_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t pm_mng_profile_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct hl_device *hdev = dev_get_drvdata(dev);

	if (hl_device_disabled_or_in_reset(hdev))
		return -ENODEV;

	return sprintf(buf, "%s\n",
			(hdev->pm_mng_profile == PM_AUTO) ? "auto" :
			(hdev->pm_mng_profile == PM_MANUAL) ? "manual" :
			"unknown");
}