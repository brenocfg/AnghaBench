#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_3__ thermal; TYPE_2__* dev; TYPE_1__ wmi; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_SERVICE_THERM_THROT ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 

void ath10k_thermal_unregister(struct ath10k *ar)
{
	if (!test_bit(WMI_SERVICE_THERM_THROT, ar->wmi.svc_map))
		return;

	sysfs_remove_link(&ar->dev->kobj, "cooling_device");
	thermal_cooling_device_unregister(ar->thermal.cdev);
}