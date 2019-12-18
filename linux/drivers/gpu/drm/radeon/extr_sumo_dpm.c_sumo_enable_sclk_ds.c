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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEEP_SLEEP_CNTL ; 
 int /*<<< orphan*/  DEEP_SLEEP_CNTL2 ; 
 int /*<<< orphan*/  ENABLE_DS ; 
 int HS (int) ; 
 int HS_MASK ; 
 int INOUT_C (int) ; 
 int INOUT_C_MASK ; 
 int LB_UFP_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int R_DIS ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sumo_enable_sclk_ds(struct radeon_device *rdev, bool enable)
{
	if (enable) {
		u32 deep_sleep_cntl = RREG32(DEEP_SLEEP_CNTL);
		u32 deep_sleep_cntl2 = RREG32(DEEP_SLEEP_CNTL2);
		u32 t = 1;

		deep_sleep_cntl &= ~R_DIS;
		deep_sleep_cntl &= ~HS_MASK;
		deep_sleep_cntl |= HS(t > 4095 ? 4095 : t);

		deep_sleep_cntl2 |= LB_UFP_EN;
		deep_sleep_cntl2 &= INOUT_C_MASK;
		deep_sleep_cntl2 |= INOUT_C(0xf);

		WREG32(DEEP_SLEEP_CNTL2, deep_sleep_cntl2);
		WREG32(DEEP_SLEEP_CNTL, deep_sleep_cntl);
	} else
		WREG32_P(DEEP_SLEEP_CNTL, 0, ~ENABLE_DS);
}