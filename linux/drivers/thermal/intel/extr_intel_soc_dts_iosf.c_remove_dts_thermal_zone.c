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
struct intel_soc_dts_sensor_entry {int /*<<< orphan*/  tzone; int /*<<< orphan*/  store_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int /*<<< orphan*/  SOC_DTS_OFFSET_ENABLE ; 
 int /*<<< orphan*/  iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_dts_thermal_zone(struct intel_soc_dts_sensor_entry *dts)
{
	if (dts) {
		iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
			       SOC_DTS_OFFSET_ENABLE, dts->store_status);
		thermal_zone_device_unregister(dts->tzone);
	}
}