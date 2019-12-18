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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;
struct ci_leakage_voltage {size_t count; int /*<<< orphan*/ * actual_voltage; int /*<<< orphan*/ * leakage_id; } ;
struct ci_power_info {struct ci_leakage_voltage vddci_leakage; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ci_patch_with_vddci_leakage(struct radeon_device *rdev, u16 *vddci)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_leakage_voltage *leakage_table = &pi->vddci_leakage;
	u32 leakage_index;

	for (leakage_index = 0; leakage_index < leakage_table->count; leakage_index++) {
		if (leakage_table->leakage_id[leakage_index] == *vddci) {
			*vddci = leakage_table->actual_voltage[leakage_index];
			break;
		}
	}
}