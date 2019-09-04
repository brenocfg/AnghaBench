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
typedef  scalar_t__ u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmRLC_CNTL ; 

__attribute__((used)) static void gfx_v7_0_update_rlc(struct amdgpu_device *adev, u32 rlc)
{
	u32 tmp;

	tmp = RREG32(mmRLC_CNTL);
	if (tmp != rlc)
		WREG32(mmRLC_CNTL, rlc);
}