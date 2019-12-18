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
 int /*<<< orphan*/  R300_DST_PIPE_CONFIG ; 
 int /*<<< orphan*/  R400_GB_PIPE_SELECT ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PLL (int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ r100_gui_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  r420_pipes_init (struct radeon_device*) ; 
 scalar_t__ rv515_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_vga_render_disable (struct radeon_device*) ; 

__attribute__((used)) static void rv515_gpu_init(struct radeon_device *rdev)
{
	unsigned pipe_select_current, gb_pipe_select, tmp;

	if (r100_gui_wait_for_idle(rdev)) {
		pr_warn("Failed to wait GUI idle while resetting GPU. Bad things might happen.\n");
	}
	rv515_vga_render_disable(rdev);
	r420_pipes_init(rdev);
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	tmp = RREG32(R300_DST_PIPE_CONFIG);
	pipe_select_current = (tmp >> 2) & 3;
	tmp = (1 << pipe_select_current) |
	      (((gb_pipe_select >> 8) & 0xF) << 4);
	WREG32_PLL(0x000D, tmp);
	if (r100_gui_wait_for_idle(rdev)) {
		pr_warn("Failed to wait GUI idle while resetting GPU. Bad things might happen.\n");
	}
	if (rv515_mc_wait_for_idle(rdev)) {
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	}
}