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
typedef  enum r600_td { ____Placeholder_r600_td } r600_td ;

/* Variables and functions */
 scalar_t__ CG_FFCT_0 ; 
 int DTC_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIR_FORCE_TREND_SEL ; 
 int /*<<< orphan*/  FIR_TREND_MODE ; 
 int R600_PM_NUMBER_OF_TC ; 
 int R600_TD_AUTO ; 
 int R600_TD_DFLT ; 
 int R600_TD_DOWN ; 
 int R600_TD_UP ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int UTC_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r600_dtc ; 
 int /*<<< orphan*/ * r600_utc ; 

void rv770_program_tp(struct radeon_device *rdev)
{
	int i;
	enum r600_td td = R600_TD_DFLT;

	for (i = 0; i < R600_PM_NUMBER_OF_TC; i++)
		WREG32(CG_FFCT_0 + (i * 4), (UTC_0(r600_utc[i]) | DTC_0(r600_dtc[i])));

	if (td == R600_TD_AUTO)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_FORCE_TREND_SEL);
	else
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_FORCE_TREND_SEL, ~FIR_FORCE_TREND_SEL);
	if (td == R600_TD_UP)
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~FIR_TREND_MODE);
	if (td == R600_TD_DOWN)
		WREG32_P(SCLK_PWRMGT_CNTL, FIR_TREND_MODE, ~FIR_TREND_MODE);
}