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
typedef  unsigned int u32 ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {int /*<<< orphan*/  crtc_id; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE8 (struct radeon_device*) ; 
 unsigned int DCCG_AUDIO_DTO0_SOURCE_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO1_MODULE ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO1_PHASE ; 
 unsigned int DCCG_AUDIO_DTO_SEL ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO_SOURCE ; 
 int /*<<< orphan*/  DCE8_DCCG_AUDIO_DTO1_MODULE ; 
 int /*<<< orphan*/  DCE8_DCCG_AUDIO_DTO1_PHASE ; 
 int /*<<< orphan*/  DENTIST_DISPCLK_CNTL ; 
 unsigned int DENTIST_DPREFCLK_WDIVIDER_MASK ; 
 unsigned int DENTIST_DPREFCLK_WDIVIDER_SHIFT ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int radeon_audio_decode_dfs_div (unsigned int) ; 

void dce6_dp_audio_set_dto(struct radeon_device *rdev,
			   struct radeon_crtc *crtc, unsigned int clock)
{
	/* Two dtos; generally use dto1 for DP */
	u32 value = 0;
	value |= DCCG_AUDIO_DTO_SEL;

	if (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel clock] as an exact rational
	 * number (coefficient of two integer numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	if (ASIC_IS_DCE8(rdev)) {
		unsigned int div = (RREG32(DENTIST_DISPCLK_CNTL) &
			DENTIST_DPREFCLK_WDIVIDER_MASK) >>
			DENTIST_DPREFCLK_WDIVIDER_SHIFT;
		div = radeon_audio_decode_dfs_div(div);

		if (div)
			clock = clock * 100 / div;

		WREG32(DCE8_DCCG_AUDIO_DTO1_PHASE, 24000);
		WREG32(DCE8_DCCG_AUDIO_DTO1_MODULE, clock);
	} else {
		WREG32(DCCG_AUDIO_DTO1_PHASE, 24000);
		WREG32(DCCG_AUDIO_DTO1_MODULE, clock);
	}
}