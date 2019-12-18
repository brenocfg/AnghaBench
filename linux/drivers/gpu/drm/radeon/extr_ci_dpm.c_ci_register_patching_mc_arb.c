#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_SEQ_MISC0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_register_patching_mc_arb(struct radeon_device *rdev,
					const u32 engine_clock,
					const u32 memory_clock,
					u32 *dram_timimg2)
{
	bool patch;
	u32 tmp, tmp2;

	tmp = RREG32(MC_SEQ_MISC0);
	patch = ((tmp & 0x0000f00) == 0x300) ? true : false;

	if (patch &&
	    ((rdev->pdev->device == 0x67B0) ||
	     (rdev->pdev->device == 0x67B1))) {
		if ((memory_clock > 100000) && (memory_clock <= 125000)) {
			tmp2 = (((0x31 * engine_clock) / 125000) - 1) & 0xff;
			*dram_timimg2 &= ~0x00ff0000;
			*dram_timimg2 |= tmp2 << 16;
		} else if ((memory_clock > 125000) && (memory_clock <= 137500)) {
			tmp2 = (((0x36 * engine_clock) / 137500) - 1) & 0xff;
			*dram_timimg2 &= ~0x00ff0000;
			*dram_timimg2 |= tmp2 << 16;
		}
	}
}