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
struct amdgpu_ring {TYPE_1__* funcs; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  emit_wreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDP ; 
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15_NO_KIQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ring_emit_wreg (struct amdgpu_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmHDP_READ_CACHE_INVALIDATE ; 

__attribute__((used)) static void nv_invalidate_hdp(struct amdgpu_device *adev,
				struct amdgpu_ring *ring)
{
	if (!ring || !ring->funcs->emit_wreg) {
		WREG32_SOC15_NO_KIQ(NBIO, 0, mmHDP_READ_CACHE_INVALIDATE, 1);
	} else {
		amdgpu_ring_emit_wreg(ring, SOC15_REG_OFFSET(
					HDP, 0, mmHDP_READ_CACHE_INVALIDATE), 1);
	}
}