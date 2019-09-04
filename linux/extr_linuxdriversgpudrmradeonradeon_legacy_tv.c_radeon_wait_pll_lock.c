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
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ RADEON_CLOCK_CNTL_DATA ; 
 scalar_t__ RADEON_CLOCK_CNTL_INDEX ; 
 int RADEON_PLL_MASK_READ_B ; 
 int /*<<< orphan*/  RADEON_PLL_TEST_CNTL ; 
 int /*<<< orphan*/  RADEON_TEST_DEBUG_MUX ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 unsigned int RREG8 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG8 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_wait_pll_lock(struct drm_encoder *encoder, unsigned n_tests,
				 unsigned n_wait_loops, unsigned cnt_threshold)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t save_pll_test;
	unsigned int i, j;

	WREG32(RADEON_TEST_DEBUG_MUX, (RREG32(RADEON_TEST_DEBUG_MUX) & 0xffff60ff) | 0x100);
	save_pll_test = RREG32_PLL(RADEON_PLL_TEST_CNTL);
	WREG32_PLL(RADEON_PLL_TEST_CNTL, save_pll_test & ~RADEON_PLL_MASK_READ_B);

	WREG8(RADEON_CLOCK_CNTL_INDEX, RADEON_PLL_TEST_CNTL);
	for (i = 0; i < n_tests; i++) {
		WREG8(RADEON_CLOCK_CNTL_DATA + 3, 0);
		for (j = 0; j < n_wait_loops; j++)
			if (RREG8(RADEON_CLOCK_CNTL_DATA + 3) >= cnt_threshold)
				break;
	}
	WREG32_PLL(RADEON_PLL_TEST_CNTL, save_pll_test);
	WREG32(RADEON_TEST_DEBUG_MUX, RREG32(RADEON_TEST_DEBUG_MUX) & 0xffffe0ff);
}