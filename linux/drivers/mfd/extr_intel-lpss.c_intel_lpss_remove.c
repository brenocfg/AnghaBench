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
struct intel_lpss {int /*<<< orphan*/  devid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct intel_lpss* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lpss_debugfs_remove (struct intel_lpss*) ; 
 int /*<<< orphan*/  intel_lpss_devid_ida ; 
 int /*<<< orphan*/  intel_lpss_ltr_hide (struct intel_lpss*) ; 
 int /*<<< orphan*/  intel_lpss_unregister_clock (struct intel_lpss*) ; 
 int /*<<< orphan*/  mfd_remove_devices (struct device*) ; 

void intel_lpss_remove(struct device *dev)
{
	struct intel_lpss *lpss = dev_get_drvdata(dev);

	mfd_remove_devices(dev);
	intel_lpss_debugfs_remove(lpss);
	intel_lpss_ltr_hide(lpss);
	intel_lpss_unregister_clock(lpss);
	ida_simple_remove(&intel_lpss_devid_ida, lpss->devid);
}