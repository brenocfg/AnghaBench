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
struct ci_power_info {scalar_t__ caps_tcp_ramping; scalar_t__ caps_td_ramping; scalar_t__ caps_db_ramping; scalar_t__ caps_sq_ramping; } ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* exit_safe_mode ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* enter_safe_mode ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ci_do_enable_didt (struct amdgpu_device*,int) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int ci_program_pt_config_registers (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  didt_config_ci ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub3 (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_enable_didt(struct amdgpu_device *adev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	int ret;

	if (pi->caps_sq_ramping || pi->caps_db_ramping ||
	    pi->caps_td_ramping || pi->caps_tcp_ramping) {
		adev->gfx.rlc.funcs->enter_safe_mode(adev);

		if (enable) {
			ret = ci_program_pt_config_registers(adev, didt_config_ci);
			if (ret) {
				adev->gfx.rlc.funcs->exit_safe_mode(adev);
				return ret;
			}
		}

		ci_do_enable_didt(adev, enable);

		adev->gfx.rlc.funcs->exit_safe_mode(adev);
	}

	return 0;
}