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
struct rv7xx_pl {int mclk; int sclk; } ;
struct TYPE_4__ {int mclk_sclk_ratio; scalar_t__ sclk_mclk_delta; } ;
struct TYPE_5__ {TYPE_1__ dyn_state; } ;
struct TYPE_6__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct amdgpu_clock_and_voltage_limits {int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 scalar_t__ btc_get_valid_mclk (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int btc_get_valid_sclk (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btc_adjust_clock_combinations(struct amdgpu_device *adev,
					  const struct amdgpu_clock_and_voltage_limits *max_limits,
					  struct rv7xx_pl *pl)
{

	if ((pl->mclk == 0) || (pl->sclk == 0))
		return;

	if (pl->mclk == pl->sclk)
		return;

	if (pl->mclk > pl->sclk) {
		if (((pl->mclk + (pl->sclk - 1)) / pl->sclk) > adev->pm.dpm.dyn_state.mclk_sclk_ratio)
			pl->sclk = btc_get_valid_sclk(adev,
						      max_limits->sclk,
						      (pl->mclk +
						      (adev->pm.dpm.dyn_state.mclk_sclk_ratio - 1)) /
						      adev->pm.dpm.dyn_state.mclk_sclk_ratio);
	} else {
		if ((pl->sclk - pl->mclk) > adev->pm.dpm.dyn_state.sclk_mclk_delta)
			pl->mclk = btc_get_valid_mclk(adev,
						      max_limits->mclk,
						      pl->sclk -
						      adev->pm.dpm.dyn_state.sclk_mclk_delta);
	}
}