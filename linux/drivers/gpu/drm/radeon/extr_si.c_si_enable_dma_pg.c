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
struct radeon_device {int pg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PG ; 
 int /*<<< orphan*/  PG_CNTL_ENABLE ; 
 int RADEON_PG_SUPPORT_SDMA ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void si_enable_dma_pg(struct radeon_device *rdev, bool enable)
{
	u32 data, orig;

	orig = data = RREG32(DMA_PG);
	if (enable && (rdev->pg_flags & RADEON_PG_SUPPORT_SDMA))
		data |= PG_CNTL_ENABLE;
	else
		data &= ~PG_CNTL_ENABLE;
	if (orig != data)
		WREG32(DMA_PG, data);
}