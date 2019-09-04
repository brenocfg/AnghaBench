#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int count; TYPE_1__* entries; } ;
struct si_power_info {TYPE_2__ leakage_voltage; } ;
struct radeon_device {int dummy; } ;
struct TYPE_3__ {int leakage_index; int /*<<< orphan*/  voltage; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int SISLANDS_LEAKAGE_INDEX0 ; 
 int SISLANDS_MAX_LEAKAGE_COUNT ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int si_get_leakage_voltage_from_leakage_index(struct radeon_device *rdev,
						     u32 index, u16 *leakage_voltage)
{
	struct si_power_info *si_pi = si_get_pi(rdev);
	int i;

	if (leakage_voltage == NULL)
		return -EINVAL;

	if ((index & 0xff00) != 0xff00)
		return -EINVAL;

	if ((index & 0xff) > SISLANDS_MAX_LEAKAGE_COUNT + 1)
		return -EINVAL;

	if (index < SISLANDS_LEAKAGE_INDEX0)
		return -EINVAL;

	for (i = 0; i < si_pi->leakage_voltage.count; i++) {
		if (si_pi->leakage_voltage.entries[i].leakage_index == index) {
			*leakage_voltage = si_pi->leakage_voltage.entries[i].voltage;
			return 0;
		}
	}
	return -EAGAIN;
}