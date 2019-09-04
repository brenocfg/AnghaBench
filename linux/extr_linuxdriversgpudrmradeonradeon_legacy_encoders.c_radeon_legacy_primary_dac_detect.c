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
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_RN50 (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_RV100 (struct radeon_device*) ; 
 int RADEON_CRTC_CRT_ON ; 
 int /*<<< orphan*/  RADEON_CRTC_EXT_CNTL ; 
 int RADEON_DAC_CMP_EN ; 
 int RADEON_DAC_CMP_OUTPUT ; 
 int /*<<< orphan*/  RADEON_DAC_CNTL ; 
 int /*<<< orphan*/  RADEON_DAC_EXT_CNTL ; 
 int RADEON_DAC_FORCE_BLANK_OFF_EN ; 
 int RADEON_DAC_FORCE_DATA_EN ; 
 int RADEON_DAC_FORCE_DATA_SEL_G ; 
 int RADEON_DAC_FORCE_DATA_SEL_RGB ; 
 int RADEON_DAC_FORCE_DATA_SHIFT ; 
 int /*<<< orphan*/  RADEON_DAC_MACRO_CNTL ; 
 int RADEON_DAC_PDWN ; 
 int RADEON_DAC_PDWN_B ; 
 int RADEON_DAC_PDWN_G ; 
 int RADEON_DAC_PDWN_R ; 
 int RADEON_DAC_RANGE_CNTL_MASK ; 
 int RADEON_DAC_RANGE_CNTL_PS2 ; 
 int RADEON_PIXCLK_ALWAYS_ONb ; 
 int RADEON_PIXCLK_DAC_ALWAYS_ONb ; 
 int /*<<< orphan*/  RADEON_VCLK_ECP_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static enum drm_connector_status radeon_legacy_primary_dac_detect(struct drm_encoder *encoder,
								  struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t vclk_ecp_cntl, crtc_ext_cntl;
	uint32_t dac_ext_cntl, dac_cntl, dac_macro_cntl, tmp;
	enum drm_connector_status found = connector_status_disconnected;
	bool color = true;

	/* just don't bother on RN50 those chip are often connected to remoting
	 * console hw and often we get failure to load detect those. So to make
	 * everyone happy report the encoder as always connected.
	 */
	if (ASIC_IS_RN50(rdev)) {
		return connector_status_connected;
	}

	/* save the regs we need */
	vclk_ecp_cntl = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
	crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
	dac_ext_cntl = RREG32(RADEON_DAC_EXT_CNTL);
	dac_cntl = RREG32(RADEON_DAC_CNTL);
	dac_macro_cntl = RREG32(RADEON_DAC_MACRO_CNTL);

	tmp = vclk_ecp_cntl &
		~(RADEON_PIXCLK_ALWAYS_ONb | RADEON_PIXCLK_DAC_ALWAYS_ONb);
	WREG32_PLL(RADEON_VCLK_ECP_CNTL, tmp);

	tmp = crtc_ext_cntl | RADEON_CRTC_CRT_ON;
	WREG32(RADEON_CRTC_EXT_CNTL, tmp);

	tmp = RADEON_DAC_FORCE_BLANK_OFF_EN |
		RADEON_DAC_FORCE_DATA_EN;

	if (color)
		tmp |= RADEON_DAC_FORCE_DATA_SEL_RGB;
	else
		tmp |= RADEON_DAC_FORCE_DATA_SEL_G;

	if (ASIC_IS_R300(rdev))
		tmp |= (0x1b6 << RADEON_DAC_FORCE_DATA_SHIFT);
	else if (ASIC_IS_RV100(rdev))
		tmp |= (0x1ac << RADEON_DAC_FORCE_DATA_SHIFT);
	else
		tmp |= (0x180 << RADEON_DAC_FORCE_DATA_SHIFT);

	WREG32(RADEON_DAC_EXT_CNTL, tmp);

	tmp = dac_cntl & ~(RADEON_DAC_RANGE_CNTL_MASK | RADEON_DAC_PDWN);
	tmp |= RADEON_DAC_RANGE_CNTL_PS2 | RADEON_DAC_CMP_EN;
	WREG32(RADEON_DAC_CNTL, tmp);

	tmp = dac_macro_cntl;
	tmp &= ~(RADEON_DAC_PDWN_R |
		 RADEON_DAC_PDWN_G |
		 RADEON_DAC_PDWN_B);

	WREG32(RADEON_DAC_MACRO_CNTL, tmp);

	mdelay(2);

	if (RREG32(RADEON_DAC_CNTL) & RADEON_DAC_CMP_OUTPUT)
		found = connector_status_connected;

	/* restore the regs we used */
	WREG32(RADEON_DAC_CNTL, dac_cntl);
	WREG32(RADEON_DAC_MACRO_CNTL, dac_macro_cntl);
	WREG32(RADEON_DAC_EXT_CNTL, dac_ext_cntl);
	WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	WREG32_PLL(RADEON_VCLK_ECP_CNTL, vclk_ecp_cntl);

	return found;
}