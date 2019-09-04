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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRBM_SOFT_RESET ; 
 int /*<<< orphan*/  SOFT_RESET_RLC ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gfx_v6_0_rlc_reset(struct amdgpu_device *adev)
{
	WREG32_FIELD(GRBM_SOFT_RESET, SOFT_RESET_RLC, 1);
	udelay(50);
	WREG32_FIELD(GRBM_SOFT_RESET, SOFT_RESET_RLC, 0);
	udelay(50);
}