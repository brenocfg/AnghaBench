#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_soc_dts_sensors {int intr_type; TYPE_1__* soc_dts; int /*<<< orphan*/  tj_max; int /*<<< orphan*/  dts_update_lock; int /*<<< orphan*/  intr_notify_lock; } ;
typedef  enum intel_soc_dts_interrupt_type { ____Placeholder_intel_soc_dts_interrupt_type } intel_soc_dts_interrupt_type ;
struct TYPE_4__ {struct intel_soc_dts_sensors* sensors; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct intel_soc_dts_sensors* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTEL_SOC_DTS_INTERRUPT_NONE ; 
 int SOC_MAX_DTS_SENSORS ; 
 int /*<<< orphan*/  THERMAL_TRIP_PASSIVE ; 
 int add_dts_thermal_zone (int,TYPE_1__*,int,int,int) ; 
 scalar_t__ get_tj_max (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iosf_mbi_available () ; 
 int /*<<< orphan*/  kfree (struct intel_soc_dts_sensors*) ; 
 struct intel_soc_dts_sensors* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dts_thermal_zone (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int update_trip_temp (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct intel_soc_dts_sensors *intel_soc_dts_iosf_init(
	enum intel_soc_dts_interrupt_type intr_type, int trip_count,
	int read_only_trip_count)
{
	struct intel_soc_dts_sensors *sensors;
	bool notification;
	u32 tj_max;
	int ret;
	int i;

	if (!iosf_mbi_available())
		return ERR_PTR(-ENODEV);

	if (!trip_count || read_only_trip_count > trip_count)
		return ERR_PTR(-EINVAL);

	if (get_tj_max(&tj_max))
		return ERR_PTR(-EINVAL);

	sensors = kzalloc(sizeof(*sensors), GFP_KERNEL);
	if (!sensors)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&sensors->intr_notify_lock);
	mutex_init(&sensors->dts_update_lock);
	sensors->intr_type = intr_type;
	sensors->tj_max = tj_max;
	if (intr_type == INTEL_SOC_DTS_INTERRUPT_NONE)
		notification = false;
	else
		notification = true;
	for (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) {
		sensors->soc_dts[i].sensors = sensors;
		ret = add_dts_thermal_zone(i, &sensors->soc_dts[i],
					   notification, trip_count,
					   read_only_trip_count);
		if (ret)
			goto err_free;
	}

	for (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) {
		ret = update_trip_temp(&sensors->soc_dts[i], 0, 0,
				       THERMAL_TRIP_PASSIVE);
		if (ret)
			goto err_remove_zone;

		ret = update_trip_temp(&sensors->soc_dts[i], 1, 0,
				       THERMAL_TRIP_PASSIVE);
		if (ret)
			goto err_remove_zone;
	}

	return sensors;
err_remove_zone:
	for (i = 0; i < SOC_MAX_DTS_SENSORS; ++i)
		remove_dts_thermal_zone(&sensors->soc_dts[i]);

err_free:
	kfree(sensors);
	return ERR_PTR(ret);
}