#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS_MASK ; 
 int GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS__SHIFT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGC_USER_SHADER_ARRAY_CONFIG ; 

__attribute__((used)) static void gfx_v7_0_set_user_cu_inactive_bitmap(struct amdgpu_device *adev,
						 u32 bitmap)
{
	u32 data;

	if (!bitmap)
		return;

	data = bitmap << GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS__SHIFT;
	data &= GC_USER_SHADER_ARRAY_CONFIG__INACTIVE_CUS_MASK;

	WREG32(mmGC_USER_SHADER_ARRAY_CONFIG, data);
}