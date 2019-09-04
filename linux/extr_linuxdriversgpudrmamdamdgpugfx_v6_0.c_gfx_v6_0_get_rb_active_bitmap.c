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
typedef  int u32 ;
struct TYPE_3__ {int max_backends_per_se; int max_sh_per_se; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKEND_DISABLE ; 
 int /*<<< orphan*/  GC_USER_RB_BACKEND_DISABLE ; 
 int REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int amdgpu_gfx_create_bitmask (int) ; 
 int /*<<< orphan*/  mmCC_RB_BACKEND_DISABLE ; 
 int /*<<< orphan*/  mmGC_USER_RB_BACKEND_DISABLE ; 

__attribute__((used)) static u32 gfx_v6_0_get_rb_active_bitmap(struct amdgpu_device *adev)
{
	u32 data, mask;

	data = RREG32(mmCC_RB_BACKEND_DISABLE) |
		RREG32(mmGC_USER_RB_BACKEND_DISABLE);

	data = REG_GET_FIELD(data, GC_USER_RB_BACKEND_DISABLE, BACKEND_DISABLE);

	mask = amdgpu_gfx_create_bitmask(adev->gfx.config.max_backends_per_se/
					 adev->gfx.config.max_sh_per_se);

	return ~data & mask;
}