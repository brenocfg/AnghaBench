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
struct radeon_device {int cg_flags; } ;

/* Variables and functions */
 int DMA0_REGISTER_OFFSET ; 
 int DMA1_REGISTER_OFFSET ; 
 int DMA_CLK_CTRL ; 
 int DMA_POWER_CNTL ; 
 int MEM_POWER_OVERRIDE ; 
 int RADEON_CG_SUPPORT_SDMA_MGCG ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 

__attribute__((used)) static void si_enable_dma_mgcg(struct radeon_device *rdev,
			       bool enable)
{
	u32 orig, data, offset;
	int i;

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_SDMA_MGCG)) {
		for (i = 0; i < 2; i++) {
			if (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			else
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data &= ~MEM_POWER_OVERRIDE;
			if (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);
			WREG32(DMA_CLK_CTRL + offset, 0x00000100);
		}
	} else {
		for (i = 0; i < 2; i++) {
			if (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			else
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data |= MEM_POWER_OVERRIDE;
			if (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);

			orig = data = RREG32(DMA_CLK_CTRL + offset);
			data = 0xff000000;
			if (data != orig)
				WREG32(DMA_CLK_CTRL + offset, data);
		}
	}
}