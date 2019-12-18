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
struct radeon_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int RREG32_MC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RS480_GART_CACHE_CNTRL ; 
 int RS480_GART_CACHE_INVALIDATE ; 
 int /*<<< orphan*/  WREG32_MC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rs400_gart_tlb_flush(struct radeon_device *rdev)
{
	uint32_t tmp;
	unsigned int timeout = rdev->usec_timeout;

	WREG32_MC(RS480_GART_CACHE_CNTRL, RS480_GART_CACHE_INVALIDATE);
	do {
		tmp = RREG32_MC(RS480_GART_CACHE_CNTRL);
		if ((tmp & RS480_GART_CACHE_INVALIDATE) == 0)
			break;
		udelay(1);
		timeout--;
	} while (timeout > 0);
	WREG32_MC(RS480_GART_CACHE_CNTRL, 0);
}