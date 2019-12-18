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
struct TYPE_3__ {int max_cu_per_sh; } ;
struct TYPE_4__ {TYPE_1__ cik; } ;
struct radeon_device {TYPE_2__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_GC_SHADER_ARRAY_CONFIG ; 
 int /*<<< orphan*/  GC_USER_SHADER_ARRAY_CONFIG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_select_se_sh (struct radeon_device*,int,int) ; 

__attribute__((used)) static u32 cik_get_cu_active_bitmap(struct radeon_device *rdev, u32 se, u32 sh)
{
	u32 mask = 0, tmp, tmp1;
	int i;

	cik_select_se_sh(rdev, se, sh);
	tmp = RREG32(CC_GC_SHADER_ARRAY_CONFIG);
	tmp1 = RREG32(GC_USER_SHADER_ARRAY_CONFIG);
	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);

	tmp &= 0xffff0000;

	tmp |= tmp1;
	tmp >>= 16;

	for (i = 0; i < rdev->config.cik.max_cu_per_sh; i ++) {
		mask <<= 1;
		mask |= 1;
	}

	return (~tmp) & mask;
}