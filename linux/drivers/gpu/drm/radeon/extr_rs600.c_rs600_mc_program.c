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
struct rv515_mc_save {int dummy; } ;
struct TYPE_2__ {int vram_start; int vram_end; } ;
struct radeon_device {TYPE_1__ mc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_000004_MC_FB_LOCATION ; 
 int /*<<< orphan*/  R_000005_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  R_000006_AGP_BASE ; 
 int /*<<< orphan*/  R_000007_AGP_BASE_2 ; 
 int /*<<< orphan*/  R_000134_HDP_FB_LOCATION ; 
 int S_000004_MC_FB_START (int) ; 
 int S_000004_MC_FB_TOP (int) ; 
 int /*<<< orphan*/  S_000134_HDP_FB_START (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_MC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rs600_mc_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_mc_resume (struct radeon_device*,struct rv515_mc_save*) ; 
 int /*<<< orphan*/  rv515_mc_stop (struct radeon_device*,struct rv515_mc_save*) ; 

__attribute__((used)) static void rs600_mc_program(struct radeon_device *rdev)
{
	struct rv515_mc_save save;

	/* Stops all mc clients */
	rv515_mc_stop(rdev, &save);

	/* Wait for mc idle */
	if (rs600_mc_wait_for_idle(rdev))
		dev_warn(rdev->dev, "Wait MC idle timeout before updating MC.\n");

	/* FIXME: What does AGP means for such chipset ? */
	WREG32_MC(R_000005_MC_AGP_LOCATION, 0x0FFFFFFF);
	WREG32_MC(R_000006_AGP_BASE, 0);
	WREG32_MC(R_000007_AGP_BASE_2, 0);
	/* Program MC */
	WREG32_MC(R_000004_MC_FB_LOCATION,
			S_000004_MC_FB_START(rdev->mc.vram_start >> 16) |
			S_000004_MC_FB_TOP(rdev->mc.vram_end >> 16));
	WREG32(R_000134_HDP_FB_LOCATION,
		S_000134_HDP_FB_START(rdev->mc.vram_start >> 16));

	rv515_mc_resume(rdev, &save);
}