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
 int /*<<< orphan*/  CG_FTV_0 ; 
 int /*<<< orphan*/  CG_FTV_1 ; 
 int /*<<< orphan*/  CG_FTV_2 ; 
 int /*<<< orphan*/  CG_FTV_3 ; 
 int /*<<< orphan*/  CG_FTV_4 ; 
 int /*<<< orphan*/  CG_FTV_5 ; 
 int /*<<< orphan*/  CG_FTV_6 ; 
 int /*<<< orphan*/  CG_FTV_7 ; 
 int RESET_BUSY_CNT ; 
 int RESET_SCLK_CNT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ci_clear_vc(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = RREG32_SMC(SCLK_PWRMGT_CNTL);
	tmp |= (RESET_SCLK_CNT | RESET_BUSY_CNT);
	WREG32_SMC(SCLK_PWRMGT_CNTL, tmp);

	WREG32_SMC(CG_FTV_0, 0);
	WREG32_SMC(CG_FTV_1, 0);
	WREG32_SMC(CG_FTV_2, 0);
	WREG32_SMC(CG_FTV_3, 0);
	WREG32_SMC(CG_FTV_4, 0);
	WREG32_SMC(CG_FTV_5, 0);
	WREG32_SMC(CG_FTV_6, 0);
	WREG32_SMC(CG_FTV_7, 0);
}