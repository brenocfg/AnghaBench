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
 int /*<<< orphan*/  RCU_GPU_BOOST_DISABLE ; 
 int RREG32_RCU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_RCU (int /*<<< orphan*/ ,int) ; 

void sumo_boost_state_enable(struct radeon_device *rdev, bool enable)
{
	u32 boost_disable = RREG32_RCU(RCU_GPU_BOOST_DISABLE);

	boost_disable &= 0xFFFFFFFE;
	boost_disable |= (enable ? 0 : 1);
	WREG32_RCU(RCU_GPU_BOOST_DISABLE, boost_disable);
}