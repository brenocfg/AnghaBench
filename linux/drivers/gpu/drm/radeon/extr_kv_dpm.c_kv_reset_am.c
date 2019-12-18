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
 int RESET_BUSY_CNT ; 
 int RESET_SCLK_CNT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kv_reset_am(struct radeon_device *rdev)
{
	u32 sclk_pwrmgt_cntl = RREG32_SMC(SCLK_PWRMGT_CNTL);

	sclk_pwrmgt_cntl |= (RESET_SCLK_CNT | RESET_BUSY_CNT);

	WREG32_SMC(SCLK_PWRMGT_CNTL, sclk_pwrmgt_cntl);
}