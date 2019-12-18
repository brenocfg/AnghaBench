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
 int /*<<< orphan*/  DCCG_AUDIO_DTO0_MODULE ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO0_PHASE ; 
 unsigned int DCCG_AUDIO_DTO0_SOURCE_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCG_AUDIO_DTO_SOURCE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,unsigned int) ; 

void dce6_hdmi_audio_set_dto(struct radeon_device *rdev,
			     struct radeon_crtc *crtc, unsigned int clock)
{
	/* Two dtos; generally use dto0 for HDMI */
	u32 value = 0;

	if (crtc)
		value |= DCCG_AUDIO_DTO0_SOURCE_SEL(crtc->crtc_id);

	WREG32(DCCG_AUDIO_DTO_SOURCE, value);

	/* Express [24MHz / target pixel clock] as an exact rational
	 * number (coefficient of two integer numbers.  DCCG_AUDIO_DTOx_PHASE
	 * is the numerator, DCCG_AUDIO_DTOx_MODULE is the denominator
	 */
	WREG32(DCCG_AUDIO_DTO0_PHASE, 24000);
	WREG32(DCCG_AUDIO_DTO0_MODULE, clock);
}