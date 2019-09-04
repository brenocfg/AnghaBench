#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pplib_wm_report_mode; } ;
struct dc {TYPE_1__ debug; TYPE_2__* current_state; } ;
struct TYPE_4__ {scalar_t__ stream_count; } ;

/* Variables and functions */
 scalar_t__ WM_REPORT_OVERRIDE ; 
 int /*<<< orphan*/  dcn10_pplib_apply_display_requirements (struct dc*,TYPE_2__*) ; 
 int /*<<< orphan*/  dcn_bw_notify_pplib_of_wm_ranges (struct dc*) ; 

__attribute__((used)) static void optimize_shared_resources(struct dc *dc)
{
	if (dc->current_state->stream_count == 0) {
		/* S0i2 message */
		dcn10_pplib_apply_display_requirements(dc, dc->current_state);
	}

	if (dc->debug.pplib_wm_report_mode == WM_REPORT_OVERRIDE)
		dcn_bw_notify_pplib_of_wm_ranges(dc);
}