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
 int /*<<< orphan*/  CG_CG_VOLTAGE_CNTL ; 
 int /*<<< orphan*/  CG_DPM_VOLTAGE_CNTL ; 
 int /*<<< orphan*/  CG_VOLTAGE_EN ; 
 int /*<<< orphan*/  DPM_VOLTAGE_EN ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sumo_enable_voltage_scaling(struct radeon_device *rdev, bool enable)
{
	if (enable) {
		WREG32_P(CG_DPM_VOLTAGE_CNTL, DPM_VOLTAGE_EN, ~DPM_VOLTAGE_EN);
		WREG32_P(CG_CG_VOLTAGE_CNTL, 0, ~CG_VOLTAGE_EN);
	} else {
		WREG32_P(CG_CG_VOLTAGE_CNTL, CG_VOLTAGE_EN, ~CG_VOLTAGE_EN);
		WREG32_P(CG_DPM_VOLTAGE_CNTL, 0, ~DPM_VOLTAGE_EN);
	}
}