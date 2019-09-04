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
struct radeon_device {int dummy; } ;
struct ci_pt_defaults {int /*<<< orphan*/  svi_load_line_vddc; int /*<<< orphan*/  svi_load_line_en; } ;
struct TYPE_2__ {int SviLoadLineTrimVddC; scalar_t__ SviLoadLineOffsetVddC; int /*<<< orphan*/  SviLoadLineVddC; int /*<<< orphan*/  SviLoadLineEn; } ;
struct ci_power_info {TYPE_1__ smc_powertune_table; struct ci_pt_defaults* powertune_defaults; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ci_populate_svi_load_line(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	const struct ci_pt_defaults *pt_defaults = pi->powertune_defaults;

	pi->smc_powertune_table.SviLoadLineEn = pt_defaults->svi_load_line_en;
	pi->smc_powertune_table.SviLoadLineVddC = pt_defaults->svi_load_line_vddc;
	pi->smc_powertune_table.SviLoadLineTrimVddC = 3;
	pi->smc_powertune_table.SviLoadLineOffsetVddC = 0;

	return 0;
}