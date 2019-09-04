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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000040_GEN_INT_CNTL ; 
 int /*<<< orphan*/  R_000044_GEN_INT_STATUS ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void r100_irq_disable(struct radeon_device *rdev)
{
	u32 tmp;

	WREG32(R_000040_GEN_INT_CNTL, 0);
	/* Wait and acknowledge irq */
	mdelay(1);
	tmp = RREG32(R_000044_GEN_INT_STATUS);
	WREG32(R_000044_GEN_INT_STATUS, tmp);
}