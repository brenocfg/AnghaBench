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
typedef  int /*<<< orphan*/  u64 ;
struct zone_device {int work_scheduled; int /*<<< orphan*/  work; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_pkg_thres_interrupt () ; 
 int /*<<< orphan*/  pkg_interrupt_cnt ; 
 int /*<<< orphan*/  pkg_temp_lock ; 
 struct zone_device* pkg_temp_thermal_get_dev (int) ; 
 int /*<<< orphan*/  pkg_thermal_schedule_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pkg_thermal_notify(u64 msr_val)
{
	int cpu = smp_processor_id();
	struct zone_device *zonedev;
	unsigned long flags;

	spin_lock_irqsave(&pkg_temp_lock, flags);
	++pkg_interrupt_cnt;

	disable_pkg_thres_interrupt();

	/* Work is per package, so scheduling it once is enough. */
	zonedev = pkg_temp_thermal_get_dev(cpu);
	if (zonedev && !zonedev->work_scheduled) {
		zonedev->work_scheduled = true;
		pkg_thermal_schedule_work(zonedev->cpu, &zonedev->work);
	}

	spin_unlock_irqrestore(&pkg_temp_lock, flags);
	return 0;
}