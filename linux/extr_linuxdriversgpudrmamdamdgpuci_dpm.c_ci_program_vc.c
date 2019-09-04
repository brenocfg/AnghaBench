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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int CISLANDS_VRC_DFLT0 ; 
 int CISLANDS_VRC_DFLT1 ; 
 int CISLANDS_VRC_DFLT2 ; 
 int CISLANDS_VRC_DFLT3 ; 
 int CISLANDS_VRC_DFLT4 ; 
 int CISLANDS_VRC_DFLT5 ; 
 int CISLANDS_VRC_DFLT6 ; 
 int CISLANDS_VRC_DFLT7 ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SCLK_PWRMGT_CNTL__RESET_BUSY_CNT_MASK ; 
 int SCLK_PWRMGT_CNTL__RESET_SCLK_CNT_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_0 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_1 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_2 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_3 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_4 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_5 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_6 ; 
 int /*<<< orphan*/  ixCG_FREQ_TRAN_VOTING_7 ; 
 int /*<<< orphan*/  ixSCLK_PWRMGT_CNTL ; 

__attribute__((used)) static void ci_program_vc(struct amdgpu_device *adev)
{
	u32 tmp;

	tmp = RREG32_SMC(ixSCLK_PWRMGT_CNTL);
	tmp &= ~(SCLK_PWRMGT_CNTL__RESET_SCLK_CNT_MASK | SCLK_PWRMGT_CNTL__RESET_BUSY_CNT_MASK);
	WREG32_SMC(ixSCLK_PWRMGT_CNTL, tmp);

	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_0, CISLANDS_VRC_DFLT0);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_1, CISLANDS_VRC_DFLT1);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_2, CISLANDS_VRC_DFLT2);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_3, CISLANDS_VRC_DFLT3);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_4, CISLANDS_VRC_DFLT4);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_5, CISLANDS_VRC_DFLT5);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_6, CISLANDS_VRC_DFLT6);
	WREG32_SMC(ixCG_FREQ_TRAN_VOTING_7, CISLANDS_VRC_DFLT7);
}