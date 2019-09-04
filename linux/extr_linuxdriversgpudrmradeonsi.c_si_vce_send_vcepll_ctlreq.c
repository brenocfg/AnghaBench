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
typedef  int uint32_t ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_VCEPLL_FUNC_CNTL ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ETIMEDOUT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int UPLL_CTLACK2_MASK ; 
 int UPLL_CTLACK_MASK ; 
 int /*<<< orphan*/  UPLL_CTLREQ_MASK ; 
 int /*<<< orphan*/  WREG32_SMC_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int si_vce_send_vcepll_ctlreq(struct radeon_device *rdev)
{
	unsigned i;

	/* make sure VCEPLL_CTLREQ is deasserted */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~UPLL_CTLREQ_MASK);

	mdelay(10);

	/* assert UPLL_CTLREQ */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, UPLL_CTLREQ_MASK, ~UPLL_CTLREQ_MASK);

	/* wait for CTLACK and CTLACK2 to get asserted */
	for (i = 0; i < 100; ++i) {
		uint32_t mask = UPLL_CTLACK_MASK | UPLL_CTLACK2_MASK;
		if ((RREG32_SMC(CG_VCEPLL_FUNC_CNTL) & mask) == mask)
			break;
		mdelay(10);
	}

	/* deassert UPLL_CTLREQ */
	WREG32_SMC_P(CG_VCEPLL_FUNC_CNTL, 0, ~UPLL_CTLREQ_MASK);

	if (i == 100) {
		DRM_ERROR("Timeout setting UVD clocks!\n");
		return -ETIMEDOUT;
	}

	return 0;
}