#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_device {struct drm_device* ddev; } ;
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CAP0_TRIG_CNTL ; 
 int /*<<< orphan*/  RADEON_CAP1_TRIG_CNTL ; 
 int RADEON_CRT2_DISP1_SEL ; 
 int RADEON_DAC2_DAC2_CLK_SEL ; 
 int RADEON_DAC2_DAC_CLK_SEL ; 
 int /*<<< orphan*/  RADEON_DAC_CNTL2 ; 
 int /*<<< orphan*/  RADEON_DISP_HW_DEBUG ; 
 int /*<<< orphan*/  RADEON_DVI_I2C_CNTL_1 ; 
 int /*<<< orphan*/  RADEON_I2C_CNTL_1 ; 
 int /*<<< orphan*/  RADEON_OV0_SCALE_CNTL ; 
 int /*<<< orphan*/  RADEON_PLL_PWRMGT_CNTL ; 
 int RADEON_PM_MODE_SEL ; 
 int /*<<< orphan*/  RADEON_SUBPIC_CNTL ; 
 int RADEON_TV_DAC_BDACPD ; 
 int RADEON_TV_DAC_BGADJ_MASK ; 
 int /*<<< orphan*/  RADEON_TV_DAC_CNTL ; 
 int RADEON_TV_DAC_DACADJ_MASK ; 
 int RADEON_TV_DAC_GDACPD ; 
 int RADEON_TV_DAC_NBLANK ; 
 int RADEON_TV_DAC_NHOLD ; 
 int RADEON_TV_DAC_PEDESTAL ; 
 int RADEON_TV_DAC_RDACPD ; 
 int RADEON_TV_DAC_STD_MASK ; 
 int RADEON_TV_DAC_STD_PS2 ; 
 int /*<<< orphan*/  RADEON_VIPH_CONTROL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 

void r100_set_common_regs(struct radeon_device *rdev)
{
	struct drm_device *dev = rdev->ddev;
	bool force_dac2 = false;
	u32 tmp;

	/* set these so they don't interfere with anything */
	WREG32(RADEON_OV0_SCALE_CNTL, 0);
	WREG32(RADEON_SUBPIC_CNTL, 0);
	WREG32(RADEON_VIPH_CONTROL, 0);
	WREG32(RADEON_I2C_CNTL_1, 0);
	WREG32(RADEON_DVI_I2C_CNTL_1, 0);
	WREG32(RADEON_CAP0_TRIG_CNTL, 0);
	WREG32(RADEON_CAP1_TRIG_CNTL, 0);

	/* always set up dac2 on rn50 and some rv100 as lots
	 * of servers seem to wire it up to a VGA port but
	 * don't report it in the bios connector
	 * table.
	 */
	switch (dev->pdev->device) {
		/* RN50 */
	case 0x515e:
	case 0x5969:
		force_dac2 = true;
		break;
		/* RV100*/
	case 0x5159:
	case 0x515a:
		/* DELL triple head servers */
		if ((dev->pdev->subsystem_vendor == 0x1028 /* DELL */) &&
		    ((dev->pdev->subsystem_device == 0x016c) ||
		     (dev->pdev->subsystem_device == 0x016d) ||
		     (dev->pdev->subsystem_device == 0x016e) ||
		     (dev->pdev->subsystem_device == 0x016f) ||
		     (dev->pdev->subsystem_device == 0x0170) ||
		     (dev->pdev->subsystem_device == 0x017d) ||
		     (dev->pdev->subsystem_device == 0x017e) ||
		     (dev->pdev->subsystem_device == 0x0183) ||
		     (dev->pdev->subsystem_device == 0x018a) ||
		     (dev->pdev->subsystem_device == 0x019a)))
			force_dac2 = true;
		break;
	}

	if (force_dac2) {
		u32 disp_hw_debug = RREG32(RADEON_DISP_HW_DEBUG);
		u32 tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
		u32 dac2_cntl = RREG32(RADEON_DAC_CNTL2);

		/* For CRT on DAC2, don't turn it on if BIOS didn't
		   enable it, even it's detected.
		*/

		/* force it to crtc0 */
		dac2_cntl &= ~RADEON_DAC2_DAC_CLK_SEL;
		dac2_cntl |= RADEON_DAC2_DAC2_CLK_SEL;
		disp_hw_debug |= RADEON_CRT2_DISP1_SEL;

		/* set up the TV DAC */
		tv_dac_cntl &= ~(RADEON_TV_DAC_PEDESTAL |
				 RADEON_TV_DAC_STD_MASK |
				 RADEON_TV_DAC_RDACPD |
				 RADEON_TV_DAC_GDACPD |
				 RADEON_TV_DAC_BDACPD |
				 RADEON_TV_DAC_BGADJ_MASK |
				 RADEON_TV_DAC_DACADJ_MASK);
		tv_dac_cntl |= (RADEON_TV_DAC_NBLANK |
				RADEON_TV_DAC_NHOLD |
				RADEON_TV_DAC_STD_PS2 |
				(0x58 << 16));

		WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
		WREG32(RADEON_DISP_HW_DEBUG, disp_hw_debug);
		WREG32(RADEON_DAC_CNTL2, dac2_cntl);
	}

	/* switch PM block to ACPI mode */
	tmp = RREG32_PLL(RADEON_PLL_PWRMGT_CNTL);
	tmp &= ~RADEON_PM_MODE_SEL;
	WREG32_PLL(RADEON_PLL_PWRMGT_CNTL, tmp);

}