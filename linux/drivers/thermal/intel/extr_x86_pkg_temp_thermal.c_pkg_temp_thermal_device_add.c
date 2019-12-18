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
typedef  int u32 ;
struct zone_device {unsigned int cpu; int tj_max; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  msr_pkg_therm_high; int /*<<< orphan*/  msr_pkg_therm_low; int /*<<< orphan*/  tzone; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_NUMBER_OF_TRIPS ; 
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clamp_val (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int get_tj_max (unsigned int,int*) ; 
 int /*<<< orphan*/  kfree (struct zone_device*) ; 
 struct zone_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max_id ; 
 int /*<<< orphan*/  pkg_temp_lock ; 
 int /*<<< orphan*/  pkg_temp_thermal_threshold_work_fn ; 
 int /*<<< orphan*/  pkg_temp_tz_params ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_register (char*,int,int,struct zone_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int topology_logical_die_id (unsigned int) ; 
 int /*<<< orphan*/  tzone_ops ; 
 struct zone_device** zones ; 

__attribute__((used)) static int pkg_temp_thermal_device_add(unsigned int cpu)
{
	int id = topology_logical_die_id(cpu);
	u32 tj_max, eax, ebx, ecx, edx;
	struct zone_device *zonedev;
	int thres_count, err;

	if (id >= max_id)
		return -ENOMEM;

	cpuid(6, &eax, &ebx, &ecx, &edx);
	thres_count = ebx & 0x07;
	if (!thres_count)
		return -ENODEV;

	thres_count = clamp_val(thres_count, 0, MAX_NUMBER_OF_TRIPS);

	err = get_tj_max(cpu, &tj_max);
	if (err)
		return err;

	zonedev = kzalloc(sizeof(*zonedev), GFP_KERNEL);
	if (!zonedev)
		return -ENOMEM;

	INIT_DELAYED_WORK(&zonedev->work, pkg_temp_thermal_threshold_work_fn);
	zonedev->cpu = cpu;
	zonedev->tj_max = tj_max;
	zonedev->tzone = thermal_zone_device_register("x86_pkg_temp",
			thres_count,
			(thres_count == MAX_NUMBER_OF_TRIPS) ? 0x03 : 0x01,
			zonedev, &tzone_ops, &pkg_temp_tz_params, 0, 0);
	if (IS_ERR(zonedev->tzone)) {
		err = PTR_ERR(zonedev->tzone);
		kfree(zonedev);
		return err;
	}
	/* Store MSR value for package thermal interrupt, to restore at exit */
	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, zonedev->msr_pkg_therm_low,
	      zonedev->msr_pkg_therm_high);

	cpumask_set_cpu(cpu, &zonedev->cpumask);
	spin_lock_irq(&pkg_temp_lock);
	zones[id] = zonedev;
	spin_unlock_irq(&pkg_temp_lock);
	return 0;
}