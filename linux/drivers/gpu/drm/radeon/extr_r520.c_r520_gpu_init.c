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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV530 ; 
 int /*<<< orphan*/  R300_DST_PIPE_CONFIG ; 
 int /*<<< orphan*/  R400_GB_PIPE_SELECT ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_PLL (int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  r420_pipes_init (struct radeon_device*) ; 
 scalar_t__ r520_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_vga_render_disable (struct radeon_device*) ; 

__attribute__((used)) static void r520_gpu_init(struct radeon_device *rdev)
{
	unsigned pipe_select_current, gb_pipe_select, tmp;

	rv515_vga_render_disable(rdev);
	/*
	 * DST_PIPE_CONFIG		0x170C
	 * GB_TILE_CONFIG		0x4018
	 * GB_FIFO_SIZE			0x4024
	 * GB_PIPE_SELECT		0x402C
	 * GB_PIPE_SELECT2              0x4124
	 *	Z_PIPE_SHIFT			0
	 *	Z_PIPE_MASK			0x000000003
	 * GB_FIFO_SIZE2                0x4128
	 *	SC_SFIFO_SIZE_SHIFT		0
	 *	SC_SFIFO_SIZE_MASK		0x000000003
	 *	SC_MFIFO_SIZE_SHIFT		2
	 *	SC_MFIFO_SIZE_MASK		0x00000000C
	 *	FG_SFIFO_SIZE_SHIFT		4
	 *	FG_SFIFO_SIZE_MASK		0x000000030
	 *	ZB_MFIFO_SIZE_SHIFT		6
	 *	ZB_MFIFO_SIZE_MASK		0x0000000C0
	 * GA_ENHANCE			0x4274
	 * SU_REG_DEST			0x42C8
	 */
	/* workaround for RV530 */
	if (rdev->family == CHIP_RV530) {
		WREG32(0x4128, 0xFF);
	}
	r420_pipes_init(rdev);
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	tmp = RREG32(R300_DST_PIPE_CONFIG);
	pipe_select_current = (tmp >> 2) & 3;
	tmp = (1 << pipe_select_current) |
	      (((gb_pipe_select >> 8) & 0xF) << 4);
	WREG32_PLL(0x000D, tmp);
	if (r520_mc_wait_for_idle(rdev)) {
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	}
}