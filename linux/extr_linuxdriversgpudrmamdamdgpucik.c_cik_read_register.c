#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ u32 ;
struct amdgpu_device {int dummy; } ;
struct TYPE_3__ {int grbm_indexed; scalar_t__ reg_offset; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* cik_allowed_read_registers ; 
 scalar_t__ cik_get_register_value (struct amdgpu_device*,int,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cik_read_register(struct amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 reg_offset, u32 *value)
{
	uint32_t i;

	*value = 0;
	for (i = 0; i < ARRAY_SIZE(cik_allowed_read_registers); i++) {
		bool indexed = cik_allowed_read_registers[i].grbm_indexed;

		if (reg_offset != cik_allowed_read_registers[i].reg_offset)
			continue;

		*value = cik_get_register_value(adev, indexed, se_num, sh_num,
						reg_offset);
		return 0;
	}
	return -EINVAL;
}