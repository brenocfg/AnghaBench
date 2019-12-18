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
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {TYPE_2__ rlc; int /*<<< orphan*/  sq_irq; int /*<<< orphan*/  cp_ecc_error_irq; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; } ;
struct amdgpu_device {TYPE_3__ gfx; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_gfx_rlc_enter_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_rlc_exit_safe_mode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_cp_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v8_0_csb_vram_unpin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_kcq_disable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_wait_for_idle (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_wait_for_rlc_idle (struct amdgpu_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v8_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_irq_put(adev, &adev->gfx.priv_reg_irq, 0);
	amdgpu_irq_put(adev, &adev->gfx.priv_inst_irq, 0);

	amdgpu_irq_put(adev, &adev->gfx.cp_ecc_error_irq, 0);

	amdgpu_irq_put(adev, &adev->gfx.sq_irq, 0);

	/* disable KCQ to avoid CPC touch memory not valid anymore */
	gfx_v8_0_kcq_disable(adev);

	if (amdgpu_sriov_vf(adev)) {
		pr_debug("For SRIOV client, shouldn't do anything.\n");
		return 0;
	}
	amdgpu_gfx_rlc_enter_safe_mode(adev);
	if (!gfx_v8_0_wait_for_idle(adev))
		gfx_v8_0_cp_enable(adev, false);
	else
		pr_err("cp is busy, skip halt cp\n");
	if (!gfx_v8_0_wait_for_rlc_idle(adev))
		adev->gfx.rlc.funcs->stop(adev);
	else
		pr_err("rlc is busy, skip halt rlc\n");
	amdgpu_gfx_rlc_exit_safe_mode(adev);

	gfx_v8_0_csb_vram_unpin(adev);

	return 0;
}