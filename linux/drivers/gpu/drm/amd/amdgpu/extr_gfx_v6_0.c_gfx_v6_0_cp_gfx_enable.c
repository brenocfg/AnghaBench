#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int num_gfx_rings; int num_compute_rings; TYPE_4__* compute_ring; TYPE_2__* gfx_ring; } ;
struct amdgpu_device {TYPE_5__ gfx; } ;
struct TYPE_8__ {int ready; } ;
struct TYPE_9__ {TYPE_3__ sched; } ;
struct TYPE_6__ {int ready; } ;
struct TYPE_7__ {TYPE_1__ sched; } ;

/* Variables and functions */
 int CP_ME_CNTL__CE_HALT_MASK ; 
 int CP_ME_CNTL__ME_HALT_MASK ; 
 int CP_ME_CNTL__PFP_HALT_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_ME_CNTL ; 
 int /*<<< orphan*/  mmSCRATCH_UMSK ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v6_0_cp_gfx_enable(struct amdgpu_device *adev, bool enable)
{
	int i;
	if (enable) {
		WREG32(mmCP_ME_CNTL, 0);
	} else {
		WREG32(mmCP_ME_CNTL, (CP_ME_CNTL__ME_HALT_MASK |
				      CP_ME_CNTL__PFP_HALT_MASK |
				      CP_ME_CNTL__CE_HALT_MASK));
		WREG32(mmSCRATCH_UMSK, 0);
		for (i = 0; i < adev->gfx.num_gfx_rings; i++)
			adev->gfx.gfx_ring[i].sched.ready = false;
		for (i = 0; i < adev->gfx.num_compute_rings; i++)
			adev->gfx.compute_ring[i].sched.ready = false;
	}
	udelay(50);
}