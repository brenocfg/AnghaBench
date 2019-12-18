#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ready; } ;
struct TYPE_10__ {TYPE_3__ sched; } ;
struct TYPE_11__ {TYPE_4__ ring; } ;
struct TYPE_12__ {int num_compute_rings; TYPE_5__ kiq; TYPE_2__* compute_ring; } ;
struct amdgpu_device {TYPE_6__ gfx; } ;
struct TYPE_7__ {int ready; } ;
struct TYPE_8__ {TYPE_1__ sched; } ;

/* Variables and functions */
 int CP_MEC_CNTL__MEC_ME1_HALT_MASK ; 
 int CP_MEC_CNTL__MEC_ME2_HALT_MASK ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15_RLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_MEC_CNTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v9_0_cp_compute_enable(struct amdgpu_device *adev, bool enable)
{
	int i;

	if (enable) {
		WREG32_SOC15_RLC(GC, 0, mmCP_MEC_CNTL, 0);
	} else {
		WREG32_SOC15_RLC(GC, 0, mmCP_MEC_CNTL,
			(CP_MEC_CNTL__MEC_ME1_HALT_MASK | CP_MEC_CNTL__MEC_ME2_HALT_MASK));
		for (i = 0; i < adev->gfx.num_compute_rings; i++)
			adev->gfx.compute_ring[i].sched.ready = false;
		adev->gfx.kiq.ring.sched.ready = false;
	}
	udelay(50);
}