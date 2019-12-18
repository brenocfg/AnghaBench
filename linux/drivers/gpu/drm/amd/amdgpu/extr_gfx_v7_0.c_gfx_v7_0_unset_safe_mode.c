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
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmRLC_GPR_REG2 ; 

__attribute__((used)) static void gfx_v7_0_unset_safe_mode(struct amdgpu_device *adev)
{
	u32 tmp;

	tmp = 0x1 | (0 << 1);
	WREG32(mmRLC_GPR_REG2, tmp);
}