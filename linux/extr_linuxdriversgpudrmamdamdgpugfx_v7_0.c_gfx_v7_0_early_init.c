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
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_4__ {TYPE_1__ rlc; int /*<<< orphan*/ * funcs; int /*<<< orphan*/  num_compute_rings; int /*<<< orphan*/  num_gfx_rings; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_MAX_COMPUTE_RINGS ; 
 int /*<<< orphan*/  GFX7_NUM_GFX_RINGS ; 
 int /*<<< orphan*/  gfx_v7_0_gfx_funcs ; 
 int /*<<< orphan*/  gfx_v7_0_rlc_funcs ; 
 int /*<<< orphan*/  gfx_v7_0_set_gds_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_set_irq_funcs (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_set_ring_funcs (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v7_0_early_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->gfx.num_gfx_rings = GFX7_NUM_GFX_RINGS;
	adev->gfx.num_compute_rings = AMDGPU_MAX_COMPUTE_RINGS;
	adev->gfx.funcs = &gfx_v7_0_gfx_funcs;
	adev->gfx.rlc.funcs = &gfx_v7_0_rlc_funcs;
	gfx_v7_0_set_ring_funcs(adev);
	gfx_v7_0_set_irq_funcs(adev);
	gfx_v7_0_set_gds_init(adev);

	return 0;
}