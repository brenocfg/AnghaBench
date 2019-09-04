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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  db_debug2; int /*<<< orphan*/  gb_addr_config; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDB_DEBUG2 ; 
 int /*<<< orphan*/  mmGB_ADDR_CONFIG ; 
 int /*<<< orphan*/  soc15_read_indexed_register (struct amdgpu_device*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint32_t soc15_get_register_value(struct amdgpu_device *adev,
					 bool indexed, u32 se_num,
					 u32 sh_num, u32 reg_offset)
{
	if (indexed) {
		return soc15_read_indexed_register(adev, se_num, sh_num, reg_offset);
	} else {
		if (reg_offset == SOC15_REG_OFFSET(GC, 0, mmGB_ADDR_CONFIG))
			return adev->gfx.config.gb_addr_config;
		else if (reg_offset == SOC15_REG_OFFSET(GC, 0, mmDB_DEBUG2))
			return adev->gfx.config.db_debug2;
		return RREG32(reg_offset);
	}
}