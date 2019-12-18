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
typedef  scalar_t__ uint32_t ;
struct timing_generator {int dummy; } ;
struct dce110_timing_generator {scalar_t__ min_v_blank; scalar_t__ min_h_sync_width; scalar_t__ min_v_sync_width; } ;
struct TYPE_2__ {scalar_t__ INTERLACE; } ;
struct dc_crtc_timing {scalar_t__ v_total; scalar_t__ v_addressable; scalar_t__ v_border_top; scalar_t__ v_border_bottom; scalar_t__ h_sync_width; scalar_t__ v_sync_width; TYPE_1__ flags; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dce110_timing_generator_validate_timing (struct timing_generator*,struct dc_crtc_timing const*,int) ; 

bool dce120_timing_generator_validate_timing(
	struct timing_generator *tg,
	const struct dc_crtc_timing *timing,
	enum signal_type signal)
{
	uint32_t interlace_factor = timing->flags.INTERLACE ? 2 : 1;
	uint32_t v_blank =
					(timing->v_total - timing->v_addressable -
					timing->v_border_top - timing->v_border_bottom) *
					interlace_factor;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	if (!dce110_timing_generator_validate_timing(
					tg,
					timing,
					signal))
		return false;


	if (v_blank < tg110->min_v_blank	||
		 timing->h_sync_width  < tg110->min_h_sync_width ||
		 timing->v_sync_width  < tg110->min_v_sync_width)
		return false;

	return true;
}