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
struct timing_generator {int dummy; } ;
struct dcn_otg_state {scalar_t__ h_total; scalar_t__ h_blank_start; scalar_t__ h_blank_end; scalar_t__ h_sync_a_end; scalar_t__ h_sync_a_start; scalar_t__ v_total; scalar_t__ v_blank_start; scalar_t__ v_blank_end; scalar_t__ v_sync_a_end; scalar_t__ v_sync_a_start; int /*<<< orphan*/  member_0; } ;
struct dc_crtc_timing {scalar_t__ h_total; scalar_t__ h_addressable; scalar_t__ h_front_porch; scalar_t__ h_sync_width; scalar_t__ v_total; scalar_t__ v_addressable; scalar_t__ v_front_porch; scalar_t__ v_sync_width; scalar_t__ h_border_left; scalar_t__ h_border_right; scalar_t__ v_border_top; scalar_t__ v_border_bottom; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  optc1_read_otg_state (int /*<<< orphan*/ ,struct dcn_otg_state*) ; 

bool optc1_is_matching_timing(struct timing_generator *tg,
		const struct dc_crtc_timing *otg_timing)
{
	struct dc_crtc_timing hw_crtc_timing = {0};
	struct dcn_otg_state s = {0};

	if (tg == NULL || otg_timing == NULL)
		return false;

	optc1_read_otg_state(DCN10TG_FROM_TG(tg), &s);

	hw_crtc_timing.h_total = s.h_total + 1;
	hw_crtc_timing.h_addressable = s.h_total - ((s.h_total - s.h_blank_start) + s.h_blank_end);
	hw_crtc_timing.h_front_porch = s.h_total + 1 - s.h_blank_start;
	hw_crtc_timing.h_sync_width = s.h_sync_a_end - s.h_sync_a_start;

	hw_crtc_timing.v_total = s.v_total + 1;
	hw_crtc_timing.v_addressable = s.v_total - ((s.v_total - s.v_blank_start) + s.v_blank_end);
	hw_crtc_timing.v_front_porch = s.v_total + 1 - s.v_blank_start;
	hw_crtc_timing.v_sync_width = s.v_sync_a_end - s.v_sync_a_start;

	if (otg_timing->h_total != hw_crtc_timing.h_total)
		return false;

	if (otg_timing->h_border_left != hw_crtc_timing.h_border_left)
		return false;

	if (otg_timing->h_addressable != hw_crtc_timing.h_addressable)
		return false;

	if (otg_timing->h_border_right != hw_crtc_timing.h_border_right)
		return false;

	if (otg_timing->h_front_porch != hw_crtc_timing.h_front_porch)
		return false;

	if (otg_timing->h_sync_width != hw_crtc_timing.h_sync_width)
		return false;

	if (otg_timing->v_total != hw_crtc_timing.v_total)
		return false;

	if (otg_timing->v_border_top != hw_crtc_timing.v_border_top)
		return false;

	if (otg_timing->v_addressable != hw_crtc_timing.v_addressable)
		return false;

	if (otg_timing->v_border_bottom != hw_crtc_timing.v_border_bottom)
		return false;

	if (otg_timing->v_sync_width != hw_crtc_timing.v_sync_width)
		return false;

	return true;
}