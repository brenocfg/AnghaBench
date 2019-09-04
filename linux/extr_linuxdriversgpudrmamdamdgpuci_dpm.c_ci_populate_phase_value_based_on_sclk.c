#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct amdgpu_phase_shedding_limits_table {unsigned int count; TYPE_1__* entries; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ sclk; } ;

/* Variables and functions */

__attribute__((used)) static void ci_populate_phase_value_based_on_sclk(struct amdgpu_device *adev,
						  const struct amdgpu_phase_shedding_limits_table *limits,
						  u32 sclk,
						  u32 *phase_shedding)
{
	unsigned int i;

	*phase_shedding = 1;

	for (i = 0; i < limits->count; i++) {
		if (sclk < limits->entries[i].sclk) {
			*phase_shedding = i;
			break;
		}
	}
}