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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct timing_generator {TYPE_1__* funcs; } ;
struct dce110_timing_generator {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_scanoutpos ) (struct timing_generator*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_VERTICAL_INTERRUPT0_POSITION ; 
 int /*<<< orphan*/  CRTC_REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CRTC_VERTICAL_INTERRUPT0_LINE_END ; 
 int /*<<< orphan*/  CRTC_VERTICAL_INTERRUPT0_LINE_START ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static bool dce120_arm_vert_intr(
		struct timing_generator *tg,
		uint8_t width)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t v_blank_start, v_blank_end, h_position, v_position;

	tg->funcs->get_scanoutpos(
				tg,
				&v_blank_start,
				&v_blank_end,
				&h_position,
				&v_position);

	if (v_blank_start == 0 || v_blank_end == 0)
		return false;

	CRTC_REG_SET_2(
			CRTC0_CRTC_VERTICAL_INTERRUPT0_POSITION,
			CRTC_VERTICAL_INTERRUPT0_LINE_START, v_blank_start,
			CRTC_VERTICAL_INTERRUPT0_LINE_END, v_blank_start + width);

	return true;
}