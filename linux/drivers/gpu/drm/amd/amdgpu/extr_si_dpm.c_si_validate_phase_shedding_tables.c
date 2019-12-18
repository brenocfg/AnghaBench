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
struct atom_voltage_table {int mask_low; int count; } ;
struct amdgpu_phase_shedding_limits_table {int count; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int hweight32 (int) ; 

__attribute__((used)) static bool si_validate_phase_shedding_tables(struct amdgpu_device *adev,
					      const struct atom_voltage_table *table,
					      const struct amdgpu_phase_shedding_limits_table *limits)
{
	u32 data, num_bits, num_levels;

	if ((table == NULL) || (limits == NULL))
		return false;

	data = table->mask_low;

	num_bits = hweight32(data);

	if (num_bits == 0)
		return false;

	num_levels = (1 << num_bits);

	if (table->count != num_levels)
		return false;

	if (limits->count != (num_levels - 1))
		return false;

	return true;
}