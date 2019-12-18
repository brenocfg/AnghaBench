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
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int RADEON_P2PLL_ATOMIC_UPDATE_R ; 
 int /*<<< orphan*/  RADEON_P2PLL_ATOMIC_UPDATE_W ; 
 int /*<<< orphan*/  RADEON_P2PLL_REF_DIV ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_PLL_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_pll2_write_update(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;

	while (RREG32_PLL(RADEON_P2PLL_REF_DIV) & RADEON_P2PLL_ATOMIC_UPDATE_R);

	WREG32_PLL_P(RADEON_P2PLL_REF_DIV,
			   RADEON_P2PLL_ATOMIC_UPDATE_W,
			   ~(RADEON_P2PLL_ATOMIC_UPDATE_W));
}