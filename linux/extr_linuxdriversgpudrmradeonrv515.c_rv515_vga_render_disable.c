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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int C_000300_VGA_VSTATUS_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000300_VGA_RENDER_CONTROL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void rv515_vga_render_disable(struct radeon_device *rdev)
{
	WREG32(R_000300_VGA_RENDER_CONTROL,
		RREG32(R_000300_VGA_RENDER_CONTROL) & C_000300_VGA_VSTATUS_CNTL);
}