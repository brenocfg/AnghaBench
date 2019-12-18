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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ max_shader_engines; scalar_t__ max_sh_per_se; scalar_t__ max_cu_per_sh; } ;
struct TYPE_4__ {TYPE_1__ si; } ;
struct radeon_device {TYPE_2__ config; } ;

/* Variables and functions */
 scalar_t__ MAX_PU_CU (scalar_t__) ; 
 scalar_t__ MAX_PU_CU_MASK ; 
 int /*<<< orphan*/  RLC_MAX_PG_CU ; 
 int /*<<< orphan*/  RLC_PG_AO_CU_MASK ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ si_get_cu_active_bitmap (struct radeon_device*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void si_init_ao_cu_mask(struct radeon_device *rdev)
{
	u32 i, j, k, active_cu_number = 0;
	u32 mask, counter, cu_bitmap;
	u32 tmp = 0;

	for (i = 0; i < rdev->config.si.max_shader_engines; i++) {
		for (j = 0; j < rdev->config.si.max_sh_per_se; j++) {
			mask = 1;
			cu_bitmap = 0;
			counter  = 0;
			for (k = 0; k < rdev->config.si.max_cu_per_sh; k++) {
				if (si_get_cu_active_bitmap(rdev, i, j) & mask) {
					if (counter < 2)
						cu_bitmap |= mask;
					counter++;
				}
				mask <<= 1;
			}

			active_cu_number += counter;
			tmp |= (cu_bitmap << (i * 16 + j * 8));
		}
	}

	WREG32(RLC_PG_AO_CU_MASK, tmp);

	tmp = RREG32(RLC_MAX_PG_CU);
	tmp &= ~MAX_PU_CU_MASK;
	tmp |= MAX_PU_CU(active_cu_number);
	WREG32(RLC_MAX_PG_CU, tmp);
}