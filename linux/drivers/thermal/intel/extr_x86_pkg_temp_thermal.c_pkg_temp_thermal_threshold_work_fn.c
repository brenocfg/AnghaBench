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
typedef  int u64 ;
struct zone_device {int work_scheduled; struct thermal_zone_device* tzone; } ;
struct work_struct {int dummy; } ;
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_STATUS ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int THERM_LOG_THRESHOLD0 ; 
 int THERM_LOG_THRESHOLD1 ; 
 int /*<<< orphan*/  enable_pkg_thres_interrupt () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkg_temp_lock ; 
 struct zone_device* pkg_temp_thermal_get_dev (int) ; 
 int /*<<< orphan*/  pkg_work_cnt ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_update (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_mutex ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pkg_temp_thermal_threshold_work_fn(struct work_struct *work)
{
	struct thermal_zone_device *tzone = NULL;
	int cpu = smp_processor_id();
	struct zone_device *zonedev;
	u64 msr_val, wr_val;

	mutex_lock(&thermal_zone_mutex);
	spin_lock_irq(&pkg_temp_lock);
	++pkg_work_cnt;

	zonedev = pkg_temp_thermal_get_dev(cpu);
	if (!zonedev) {
		spin_unlock_irq(&pkg_temp_lock);
		mutex_unlock(&thermal_zone_mutex);
		return;
	}
	zonedev->work_scheduled = false;

	rdmsrl(MSR_IA32_PACKAGE_THERM_STATUS, msr_val);
	wr_val = msr_val & ~(THERM_LOG_THRESHOLD0 | THERM_LOG_THRESHOLD1);
	if (wr_val != msr_val) {
		wrmsrl(MSR_IA32_PACKAGE_THERM_STATUS, wr_val);
		tzone = zonedev->tzone;
	}

	enable_pkg_thres_interrupt();
	spin_unlock_irq(&pkg_temp_lock);

	/*
	 * If tzone is not NULL, then thermal_zone_mutex will prevent the
	 * concurrent removal in the cpu offline callback.
	 */
	if (tzone)
		thermal_zone_device_update(tzone, THERMAL_EVENT_UNSPECIFIED);

	mutex_unlock(&thermal_zone_mutex);
}