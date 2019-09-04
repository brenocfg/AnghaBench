#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sumo_vid_mapping_table {size_t num_entries; TYPE_5__* entries; } ;
struct radeon_clock_voltage_dependency_table {size_t count; TYPE_4__* entries; } ;
struct TYPE_6__ {struct radeon_clock_voltage_dependency_table vddc_dependency_on_sclk; } ;
struct TYPE_7__ {TYPE_1__ dyn_state; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_10__ {size_t vid_2bit; size_t vid_7bit; } ;
struct TYPE_9__ {size_t v; } ;

/* Variables and functions */

__attribute__((used)) static u32 kv_convert_vid2_to_vid7(struct radeon_device *rdev,
				   struct sumo_vid_mapping_table *vid_mapping_table,
				   u32 vid_2bit)
{
	struct radeon_clock_voltage_dependency_table *vddc_sclk_table =
		&rdev->pm.dpm.dyn_state.vddc_dependency_on_sclk;
	u32 i;

	if (vddc_sclk_table && vddc_sclk_table->count) {
		if (vid_2bit < vddc_sclk_table->count)
			return vddc_sclk_table->entries[vid_2bit].v;
		else
			return vddc_sclk_table->entries[vddc_sclk_table->count - 1].v;
	} else {
		for (i = 0; i < vid_mapping_table->num_entries; i++) {
			if (vid_mapping_table->entries[i].vid_2bit == vid_2bit)
				return vid_mapping_table->entries[i].vid_7bit;
		}
		return vid_mapping_table->entries[vid_mapping_table->num_entries - 1].vid_7bit;
	}
}