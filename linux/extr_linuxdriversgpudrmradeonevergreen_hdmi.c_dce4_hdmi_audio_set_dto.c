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
 int /*<<< orphan*/  DCCG_AUDIO_DTO0_CNTL ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO0_MODULE ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO0_PHASE ; 
 unsigned int DCCG_AUDIO_DTO0_SOURCE_SEL (int /*<<< orphan*/ ) ; 
 unsigned int DCCG_AUDIO_DTO1_USE_512FBR_DTO ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO_SOURCE ; 
 unsigned int DCCG_AUDIO_DTO_WALLCLOCK_RATIO (unsigned int) ; 
 unsigned int DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,unsigned int) ; 

void dce4_hdmi_audio_set_dto(struct radeon_device *rdev,
	struct radeon_crtc *crtc, unsigned int clock)
{
	unsigned int max_ratio = clock / 24000;
	u32 dto_phase;
	u32 wallclock_ratio;
	u32 value;

	if (max_ratio >= 8) {
		dto_phase = 192 * 1000;
		wallclock_ratio = 3;
	} else if (max_ratio >= 4) {
		dto_phase = 96 * 1000;
		wallclock_ratio = 2;
	} else if (max_ratio >= 2) {
		dto_phase = 48 * 1000;
		wallclock_ratio = 1;
	} else {
		dto_phase = 24 * 1000;
		wallclock_ratio = 0;
	}

	value = RREG32(DCCG_AUDIO_DTO0_CNTL) & ~DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK;
	value |= DCCG_AUDIO_DTO_WALLCLOCK_RATIO(wallclock_ratio);
	value &= ~DCCG_AUDIO_DTO1_USE_512FBR_DTO;
	WREG32(DCCG_AUDIO_DTO0_CNTL, value);

	/* Two dtos; generally use dto0 for HDMI */
	value = 0;

	if (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel clock] as an exact rational
	 * number (coefficient of two integer numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	WREG32(DCCG_AUDIO_DTO0_PHASE, dto_phase);
	WREG32(DCCG_AUDIO_DTO0_MODULE, clock);
}