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
 int /*<<< orphan*/  CG_SCLK_DPM_CTRL_3 ; 
 int /*<<< orphan*/  CNB_THERMTHRO_MASK_SCLK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sumo_override_cnb_thermal_events(struct radeon_device *rdev)
{
	WREG32_P(CG_SCLK_DPM_CTRL_3, CNB_THERMTHRO_MASK_SCLK,
		 ~CNB_THERMTHRO_MASK_SCLK);
}