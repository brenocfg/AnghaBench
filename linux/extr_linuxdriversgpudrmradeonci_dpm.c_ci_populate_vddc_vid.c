#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_5__ {int count; TYPE_3__* entries; } ;
struct TYPE_4__ {int /*<<< orphan*/ * VddCVid; } ;
struct ci_power_info {TYPE_2__ vddc_voltage_table; TYPE_1__ smc_powertune_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ci_convert_to_vid (int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_populate_vddc_vid(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u8 *vid = pi->smc_powertune_table.VddCVid;
	u32 i;

	if (pi->vddc_voltage_table.count > 8)
		return -EINVAL;

	for (i = 0; i < pi->vddc_voltage_table.count; i++)
		vid[i] = ci_convert_to_vid(pi->vddc_voltage_table.entries[i].value);

	return 0;
}