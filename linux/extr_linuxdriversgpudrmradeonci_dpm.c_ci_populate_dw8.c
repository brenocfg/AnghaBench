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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct ci_pt_defaults {scalar_t__ tdc_waterfall_ctl; } ;
struct TYPE_2__ {scalar_t__ TdcWaterfallCtl; } ;
struct ci_power_info {TYPE_1__ smc_powertune_table; int /*<<< orphan*/  sram_end; struct ci_pt_defaults* powertune_defaults; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PmFuseTable ; 
 int /*<<< orphan*/  SMU7_Discrete_PmFuses ; 
 scalar_t__ SMU7_FIRMWARE_HEADER_LOCATION ; 
 int /*<<< orphan*/  SMU7_Firmware_Header ; 
 int /*<<< orphan*/  TdcWaterfallCtl ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int ci_read_smc_sram_dword (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_populate_dw8(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	const struct ci_pt_defaults *pt_defaults = pi->powertune_defaults;
	int ret;

	ret = ci_read_smc_sram_dword(rdev,
				     SMU7_FIRMWARE_HEADER_LOCATION +
				     offsetof(SMU7_Firmware_Header, PmFuseTable) +
				     offsetof(SMU7_Discrete_PmFuses, TdcWaterfallCtl),
				     (u32 *)&pi->smc_powertune_table.TdcWaterfallCtl,
				     pi->sram_end);
	if (ret)
		return -EINVAL;
	else
		pi->smc_powertune_table.TdcWaterfallCtl = pt_defaults->tdc_waterfall_ctl;

	return 0;
}