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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int RADEON_BLU_MX_FORCE_DAC_DATA ; 
 int RADEON_CFG_ATI_REV_ID_MASK ; 
 int RADEON_CMP_BLU_EN ; 
 int /*<<< orphan*/  RADEON_CONFIG_CNTL ; 
 int RADEON_CRT_ASYNC_RST ; 
 int RADEON_CRT_FIFO_CE_EN ; 
 int RADEON_C_GRN_EN ; 
 int RADEON_DAC2_DAC2_CLK_SEL ; 
 int /*<<< orphan*/  RADEON_DAC_CNTL2 ; 
 int RADEON_GRN_MX_FORCE_DAC_DATA ; 
 int RADEON_RED_MX_FORCE_DAC_DATA ; 
 int RADEON_RESTART_PHASE_FIX ; 
 int RADEON_RE_SYNC_NOW_SEL_MASK ; 
 int RADEON_TV_ASYNC_RST ; 
 int RADEON_TV_DAC_BDACDET ; 
 int RADEON_TV_DAC_BGADJ_SHIFT ; 
 int /*<<< orphan*/  RADEON_TV_DAC_CNTL ; 
 int RADEON_TV_DAC_DACADJ_SHIFT ; 
 int RADEON_TV_DAC_GDACDET ; 
 int RADEON_TV_DAC_NBLANK ; 
 int RADEON_TV_DAC_NHOLD ; 
 int RADEON_TV_DAC_STD_NTSC ; 
 int RADEON_TV_FIFO_ASYNC_RST ; 
 int RADEON_TV_FIFO_CE_EN ; 
 int RADEON_TV_FORCE_DAC_DATA_SHIFT ; 
 int /*<<< orphan*/  RADEON_TV_MASTER_CNTL ; 
 int RADEON_TV_MONITOR_DETECT_EN ; 
 int RADEON_TV_ON ; 
 int /*<<< orphan*/  RADEON_TV_PRE_DAC_MUX_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int r300_legacy_tv_detect (struct drm_encoder*,struct drm_connector*) ; 

__attribute__((used)) static bool radeon_legacy_tv_detect(struct drm_encoder *encoder,
				    struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t tv_dac_cntl, dac_cntl2;
	uint32_t config_cntl, tv_pre_dac_mux_cntl, tv_master_cntl, tmp;
	bool found = false;

	if (ASIC_IS_R300(rdev))
		return r300_legacy_tv_detect(encoder, connector);

	dac_cntl2 = RREG32(RADEON_DAC_CNTL2);
	tv_master_cntl = RREG32(RADEON_TV_MASTER_CNTL);
	tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
	config_cntl = RREG32(RADEON_CONFIG_CNTL);
	tv_pre_dac_mux_cntl = RREG32(RADEON_TV_PRE_DAC_MUX_CNTL);

	tmp = dac_cntl2 & ~RADEON_DAC2_DAC2_CLK_SEL;
	WREG32(RADEON_DAC_CNTL2, tmp);

	tmp = tv_master_cntl | RADEON_TV_ON;
	tmp &= ~(RADEON_TV_ASYNC_RST |
		 RADEON_RESTART_PHASE_FIX |
		 RADEON_CRT_FIFO_CE_EN |
		 RADEON_TV_FIFO_CE_EN |
		 RADEON_RE_SYNC_NOW_SEL_MASK);
	tmp |= RADEON_TV_FIFO_ASYNC_RST | RADEON_CRT_ASYNC_RST;
	WREG32(RADEON_TV_MASTER_CNTL, tmp);

	tmp = RADEON_TV_DAC_NBLANK | RADEON_TV_DAC_NHOLD |
		RADEON_TV_MONITOR_DETECT_EN | RADEON_TV_DAC_STD_NTSC |
		(8 << RADEON_TV_DAC_BGADJ_SHIFT);

	if (config_cntl & RADEON_CFG_ATI_REV_ID_MASK)
		tmp |= (4 << RADEON_TV_DAC_DACADJ_SHIFT);
	else
		tmp |= (8 << RADEON_TV_DAC_DACADJ_SHIFT);
	WREG32(RADEON_TV_DAC_CNTL, tmp);

	tmp = RADEON_C_GRN_EN | RADEON_CMP_BLU_EN |
		RADEON_RED_MX_FORCE_DAC_DATA |
		RADEON_GRN_MX_FORCE_DAC_DATA |
		RADEON_BLU_MX_FORCE_DAC_DATA |
		(0x109 << RADEON_TV_FORCE_DAC_DATA_SHIFT);
	WREG32(RADEON_TV_PRE_DAC_MUX_CNTL, tmp);

	mdelay(3);
	tmp = RREG32(RADEON_TV_DAC_CNTL);
	if (tmp & RADEON_TV_DAC_GDACDET) {
		found = true;
		DRM_DEBUG_KMS("S-video TV connection detected\n");
	} else if ((tmp & RADEON_TV_DAC_BDACDET) != 0) {
		found = true;
		DRM_DEBUG_KMS("Composite TV connection detected\n");
	}

	WREG32(RADEON_TV_PRE_DAC_MUX_CNTL, tv_pre_dac_mux_cntl);
	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
	WREG32(RADEON_TV_MASTER_CNTL, tv_master_cntl);
	WREG32(RADEON_DAC_CNTL2, dac_cntl2);
	return found;
}