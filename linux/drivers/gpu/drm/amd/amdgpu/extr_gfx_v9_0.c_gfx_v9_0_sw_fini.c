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
struct ras_common_if {int dummy; } ;
struct ras_ih_if {struct ras_common_if head; } ;
struct TYPE_5__ {int /*<<< orphan*/  cp_table_ptr; int /*<<< orphan*/  cp_table_gpu_addr; int /*<<< orphan*/  cp_table_obj; int /*<<< orphan*/  clear_state_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  ring; } ;
struct TYPE_6__ {int num_gfx_rings; int num_compute_rings; TYPE_2__ rlc; TYPE_1__ kiq; int /*<<< orphan*/ * compute_ring; int /*<<< orphan*/ * gfx_ring; struct ras_common_if* ras_if; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_3__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_RAS_BLOCK__GFX ; 
 scalar_t__ CHIP_RAVEN ; 
 scalar_t__ CHIP_RENOIR ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_gfx_kiq_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gfx_kiq_free_ring (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_gfx_mqd_sw_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_debugfs_remove (struct amdgpu_device*,struct ras_common_if*) ; 
 int /*<<< orphan*/  amdgpu_ras_feature_enable (struct amdgpu_device*,struct ras_common_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ras_interrupt_remove_handler (struct amdgpu_device*,struct ras_ih_if*) ; 
 scalar_t__ amdgpu_ras_is_supported (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ras_sysfs_remove (struct amdgpu_device*,struct ras_common_if*) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfx_v9_0_free_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_mec_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_ngg_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kfree (struct ras_common_if*) ; 

__attribute__((used)) static int gfx_v9_0_sw_fini(void *handle)
{
	int i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__GFX) &&
			adev->gfx.ras_if) {
		struct ras_common_if *ras_if = adev->gfx.ras_if;
		struct ras_ih_if ih_info = {
			.head = *ras_if,
		};

		amdgpu_ras_debugfs_remove(adev, ras_if);
		amdgpu_ras_sysfs_remove(adev, ras_if);
		amdgpu_ras_interrupt_remove_handler(adev,  &ih_info);
		amdgpu_ras_feature_enable(adev, ras_if, 0);
		kfree(ras_if);
	}

	for (i = 0; i < adev->gfx.num_gfx_rings; i++)
		amdgpu_ring_fini(&adev->gfx.gfx_ring[i]);
	for (i = 0; i < adev->gfx.num_compute_rings; i++)
		amdgpu_ring_fini(&adev->gfx.compute_ring[i]);

	amdgpu_gfx_mqd_sw_fini(adev);
	amdgpu_gfx_kiq_free_ring(&adev->gfx.kiq.ring, &adev->gfx.kiq.irq);
	amdgpu_gfx_kiq_fini(adev);

	gfx_v9_0_mec_fini(adev);
	gfx_v9_0_ngg_fini(adev);
	amdgpu_bo_unref(&adev->gfx.rlc.clear_state_obj);
	if (adev->asic_type == CHIP_RAVEN || adev->asic_type == CHIP_RENOIR) {
		amdgpu_bo_free_kernel(&adev->gfx.rlc.cp_table_obj,
				&adev->gfx.rlc.cp_table_gpu_addr,
				(void **)&adev->gfx.rlc.cp_table_ptr);
	}
	gfx_v9_0_free_microcode(adev);

	return 0;
}