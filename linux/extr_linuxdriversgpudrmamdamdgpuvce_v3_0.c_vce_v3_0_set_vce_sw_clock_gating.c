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
 int RREG32 (int /*<<< orphan*/ ) ; 
 int VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK ; 
 int VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK ; 
 int VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_B ; 
 int /*<<< orphan*/  mmVCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  mmVCE_UENC_CLOCK_GATING_2 ; 
 int /*<<< orphan*/  mmVCE_UENC_DMA_DCLK_CTRL ; 
 int /*<<< orphan*/  mmVCE_UENC_REG_CLOCK_GATING ; 
 int /*<<< orphan*/  vce_v3_0_override_vce_clock_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static void vce_v3_0_set_vce_sw_clock_gating(struct amdgpu_device *adev,
					     bool gated)
{
	u32 data;

	/* Set Override to disable Clock Gating */
	vce_v3_0_override_vce_clock_gating(adev, true);

	/* This function enables MGCG which is controlled by firmware.
	   With the clocks in the gated state the core is still
	   accessible but the firmware will throttle the clocks on the
	   fly as necessary.
	*/
	if (!gated) {
		data = RREG32(mmVCE_CLOCK_GATING_B);
		data |= 0x1ff;
		data &= ~0xef0000;
		WREG32(mmVCE_CLOCK_GATING_B, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING);
		data |= 0x3ff000;
		data &= ~0xffc00000;
		WREG32(mmVCE_UENC_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING_2);
		data |= 0x2;
		data &= ~0x00010000;
		WREG32(mmVCE_UENC_CLOCK_GATING_2, data);

		data = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
		data |= 0x37f;
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_DMA_DCLK_CTRL);
		data |= VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK |
			VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK |
			VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK  |
			0x8;
		WREG32(mmVCE_UENC_DMA_DCLK_CTRL, data);
	} else {
		data = RREG32(mmVCE_CLOCK_GATING_B);
		data &= ~0x80010;
		data |= 0xe70008;
		WREG32(mmVCE_CLOCK_GATING_B, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING);
		data |= 0xffc00000;
		WREG32(mmVCE_UENC_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING_2);
		data |= 0x10000;
		WREG32(mmVCE_UENC_CLOCK_GATING_2, data);

		data = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
		data &= ~0x3ff;
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_DMA_DCLK_CTRL);
		data &= ~(VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK |
			  VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK |
			  VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK  |
			  0x8);
		WREG32(mmVCE_UENC_DMA_DCLK_CTRL, data);
	}
	vce_v3_0_override_vce_clock_gating(adev, false);
}