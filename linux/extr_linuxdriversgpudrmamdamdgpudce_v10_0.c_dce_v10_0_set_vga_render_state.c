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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGA_HDP_CONTROL ; 
 int /*<<< orphan*/  VGA_MEMORY_DISABLE ; 
 int /*<<< orphan*/  VGA_RENDER_CONTROL ; 
 int /*<<< orphan*/  VGA_VSTATUS_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmVGA_HDP_CONTROL ; 
 int /*<<< orphan*/  mmVGA_RENDER_CONTROL ; 

__attribute__((used)) static void dce_v10_0_set_vga_render_state(struct amdgpu_device *adev,
					   bool render)
{
	u32 tmp;

	/* Lockout access through VGA aperture*/
	tmp = RREG32(mmVGA_HDP_CONTROL);
	if (render)
		tmp = REG_SET_FIELD(tmp, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 0);
	else
		tmp = REG_SET_FIELD(tmp, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 1);
	WREG32(mmVGA_HDP_CONTROL, tmp);

	/* disable VGA render */
	tmp = RREG32(mmVGA_RENDER_CONTROL);
	if (render)
		tmp = REG_SET_FIELD(tmp, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 1);
	else
		tmp = REG_SET_FIELD(tmp, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 0);
	WREG32(mmVGA_RENDER_CONTROL, tmp);
}