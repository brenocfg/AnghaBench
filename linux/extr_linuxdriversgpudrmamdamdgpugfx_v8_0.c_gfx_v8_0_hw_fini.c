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
struct TYPE_3__ {int /*<<< orphan*/  ring; } ;
struct TYPE_4__ {int num_compute_rings; int /*<<< orphan*/ * compute_ring; TYPE_1__ kiq; int /*<<< orphan*/  sq_irq; int /*<<< orphan*/  cp_ecc_error_irq; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_IP_BLOCK_TYPE_GFX ; 
 int /*<<< orphan*/  AMD_PG_STATE_UNGATE ; 
 int /*<<< orphan*/  amdgpu_device_ip_set_powergating_state (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_cp_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v8_0_kcq_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_v8_0_rlc_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int gfx_v8_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i;

	amdgpu_irq_put(adev, &adev->gfx.priv_reg_irq, 0);
	amdgpu_irq_put(adev, &adev->gfx.priv_inst_irq, 0);

	amdgpu_irq_put(adev, &adev->gfx.cp_ecc_error_irq, 0);

	amdgpu_irq_put(adev, &adev->gfx.sq_irq, 0);

	/* disable KCQ to avoid CPC touch memory not valid anymore */
	for (i = 0; i < adev->gfx.num_compute_rings; i++)
		gfx_v8_0_kcq_disable(&adev->gfx.kiq.ring, &adev->gfx.compute_ring[i]);

	if (amdgpu_sriov_vf(adev)) {
		pr_debug("For SRIOV client, shouldn't do anything.\n");
		return 0;
	}
	gfx_v8_0_cp_enable(adev, false);
	gfx_v8_0_rlc_stop(adev);

	amdgpu_device_ip_set_powergating_state(adev,
					       AMD_IP_BLOCK_TYPE_GFX,
					       AMD_PG_STATE_UNGATE);

	return 0;
}