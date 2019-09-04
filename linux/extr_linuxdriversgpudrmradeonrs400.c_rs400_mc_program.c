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
struct TYPE_2__ {int vram_start; int vram_end; } ;
struct radeon_device {TYPE_1__ mc; int /*<<< orphan*/  dev; } ;
struct r100_mc_save {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_000148_MC_FB_LOCATION ; 
 int S_000148_MC_FB_START (int) ; 
 int S_000148_MC_FB_TOP (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r100_mc_resume (struct radeon_device*,struct r100_mc_save*) ; 
 int /*<<< orphan*/  r100_mc_stop (struct radeon_device*,struct r100_mc_save*) ; 
 scalar_t__ rs400_mc_wait_for_idle (struct radeon_device*) ; 

__attribute__((used)) static void rs400_mc_program(struct radeon_device *rdev)
{
	struct r100_mc_save save;

	/* Stops all mc clients */
	r100_mc_stop(rdev, &save);

	/* Wait for mc idle */
	if (rs400_mc_wait_for_idle(rdev))
		dev_warn(rdev->dev, "rs400: Wait MC idle timeout before updating MC.\n");
	WREG32(R_000148_MC_FB_LOCATION,
		S_000148_MC_FB_START(rdev->mc.vram_start >> 16) |
		S_000148_MC_FB_TOP(rdev->mc.vram_end >> 16));

	r100_mc_resume(rdev, &save);
}