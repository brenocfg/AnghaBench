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
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit_safe_mode ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* enter_safe_mode ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vega10_didt_set_mask (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int vega10_disable_se_edc_config(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;

	adev->gfx.rlc.funcs->enter_safe_mode(adev);

	vega10_didt_set_mask(hwmgr, false);

	adev->gfx.rlc.funcs->exit_safe_mode(adev);

	return 0;
}