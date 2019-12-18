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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;
struct dc_crtc_timing {int dummy; } ;
struct crtc_stereo_flags {scalar_t__ FRAME_PACKED; scalar_t__ RIGHT_EYE_POLARITY; scalar_t__ PROGRAM_STEREO; scalar_t__ DISABLE_STEREO_DP_SYNC; scalar_t__ PROGRAM_POLARITY; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_3D_STRUCTURE_CONTROL ; 
 int /*<<< orphan*/  OTG_3D_STRUCTURE_EN ; 
 int /*<<< orphan*/  OTG_3D_STRUCTURE_STEREO_SEL_OVR ; 
 int /*<<< orphan*/  OTG_DISABLE_STEREOSYNC_OUTPUT_FOR_DP ; 
 int /*<<< orphan*/  OTG_STEREO_CONTROL ; 
 int /*<<< orphan*/  OTG_STEREO_EN ; 
 int /*<<< orphan*/  OTG_STEREO_EYE_FLAG_POLARITY ; 
 int /*<<< orphan*/  OTG_STEREO_SYNC_OUTPUT_LINE_NUM ; 
 int /*<<< orphan*/  OTG_STEREO_SYNC_OUTPUT_POLARITY ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void optc1_enable_stereo(struct timing_generator *optc,
	const struct dc_crtc_timing *timing, struct crtc_stereo_flags *flags)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	if (flags) {
		uint32_t stereo_en;
		stereo_en = flags->FRAME_PACKED == 0 ? 1 : 0;

		if (flags->PROGRAM_STEREO)
			REG_UPDATE_3(OTG_STEREO_CONTROL,
				OTG_STEREO_EN, stereo_en,
				OTG_STEREO_SYNC_OUTPUT_LINE_NUM, 0,
				OTG_STEREO_SYNC_OUTPUT_POLARITY, 0);

		if (flags->PROGRAM_POLARITY)
			REG_UPDATE(OTG_STEREO_CONTROL,
				OTG_STEREO_EYE_FLAG_POLARITY,
				flags->RIGHT_EYE_POLARITY == 0 ? 0 : 1);

		if (flags->DISABLE_STEREO_DP_SYNC)
			REG_UPDATE(OTG_STEREO_CONTROL,
				OTG_DISABLE_STEREOSYNC_OUTPUT_FOR_DP, 1);

		if (flags->PROGRAM_STEREO)
			REG_UPDATE_2(OTG_3D_STRUCTURE_CONTROL,
				OTG_3D_STRUCTURE_EN, flags->FRAME_PACKED,
				OTG_3D_STRUCTURE_STEREO_SEL_OVR, flags->FRAME_PACKED);

	}
}