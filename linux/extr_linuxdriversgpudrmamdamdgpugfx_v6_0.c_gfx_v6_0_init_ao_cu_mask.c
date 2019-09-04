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
struct TYPE_3__ {int ao_cu_mask; int number; } ;
struct TYPE_4__ {TYPE_1__ cu_info; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int RLC_MAX_PG_CU__MAX_POWERED_UP_CU_MASK ; 
 int RLC_MAX_PG_CU__MAX_POWERED_UP_CU__SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmRLC_MAX_PG_CU ; 
 int /*<<< orphan*/  mmRLC_PG_ALWAYS_ON_CU_MASK ; 

__attribute__((used)) static void gfx_v6_0_init_ao_cu_mask(struct amdgpu_device *adev)
{
	u32 tmp;

	WREG32(mmRLC_PG_ALWAYS_ON_CU_MASK, adev->gfx.cu_info.ao_cu_mask);

	tmp = RREG32(mmRLC_MAX_PG_CU);
	tmp &= ~RLC_MAX_PG_CU__MAX_POWERED_UP_CU_MASK;
	tmp |= (adev->gfx.cu_info.number << RLC_MAX_PG_CU__MAX_POWERED_UP_CU__SHIFT);
	WREG32(mmRLC_MAX_PG_CU, tmp);
}