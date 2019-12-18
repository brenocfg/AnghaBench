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
struct TYPE_2__ {int /*<<< orphan*/  num_compute_rings; scalar_t__ num_gfx_rings; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_MAX_COMPUTE_RINGS ; 
 scalar_t__ CHIP_ARCTURUS ; 
 scalar_t__ GFX9_NUM_GFX_RINGS ; 
 int /*<<< orphan*/  gfx_v9_0_set_gds_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_set_ring_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_set_rlc_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v9_0_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev->asic_type == CHIP_ARCTURUS)
		adev->gfx.num_gfx_rings = 0;
	else
		adev->gfx.num_gfx_rings = GFX9_NUM_GFX_RINGS;
	adev->gfx.num_compute_rings = AMDGPU_MAX_COMPUTE_RINGS;
	gfx_v9_0_set_ring_funcs(adev);
	gfx_v9_0_set_irq_funcs(adev);
	gfx_v9_0_set_gds_init(adev);
	gfx_v9_0_set_rlc_funcs(adev);

	return 0;
}