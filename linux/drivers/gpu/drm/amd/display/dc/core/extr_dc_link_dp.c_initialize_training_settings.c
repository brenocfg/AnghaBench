#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {scalar_t__ link_rate; scalar_t__ lane_count; void* link_spread; int /*<<< orphan*/  link_rate_set; int /*<<< orphan*/  use_link_rate_set; } ;
struct link_training_settings {int enhanced_framing; int /*<<< orphan*/  pattern_for_eq; void* eq_pattern_time; void* cr_pattern_time; int /*<<< orphan*/ * post_cursor2; TYPE_3__* lane_settings; int /*<<< orphan*/ * pre_emphasis; int /*<<< orphan*/ * voltage_swing; TYPE_2__ link_settings; } ;
struct dc_link_training_overrides {int* enhanced_framing; int /*<<< orphan*/ * pattern_for_eq; void** eq_pattern_time; void** cr_pattern_time; int /*<<< orphan*/ * post_cursor2; int /*<<< orphan*/ * pre_emphasis; int /*<<< orphan*/ * voltage_swing; scalar_t__* downspread; } ;
struct dc_link_settings {scalar_t__ link_rate; scalar_t__ lane_count; int /*<<< orphan*/  link_rate_set; int /*<<< orphan*/  use_link_rate_set; } ;
struct TYPE_4__ {scalar_t__ link_rate; scalar_t__ lane_count; } ;
struct dc_link {scalar_t__ dp_ss_off; TYPE_1__ preferred_link_setting; } ;
struct TYPE_6__ {int /*<<< orphan*/  POST_CURSOR2; int /*<<< orphan*/  PRE_EMPHASIS; int /*<<< orphan*/  VOLTAGE_SWING; } ;

/* Variables and functions */
 size_t LANE_COUNT_DP_MAX ; 
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 scalar_t__ LINK_RATE_UNKNOWN ; 
 void* LINK_SPREAD_05_DOWNSPREAD_30KHZ ; 
 void* LINK_SPREAD_DISABLED ; 
 int /*<<< orphan*/  POST_CURSOR2_DISABLED ; 
 int /*<<< orphan*/  PRE_EMPHASIS_DISABLED ; 
 int /*<<< orphan*/  VOLTAGE_SWING_LEVEL0 ; 
 int /*<<< orphan*/  get_supported_tp (struct dc_link*) ; 
 void* get_training_aux_rd_interval (struct dc_link*,int) ; 
 int /*<<< orphan*/  memset (struct link_training_settings*,char,int) ; 

__attribute__((used)) static void initialize_training_settings(
	 struct dc_link *link,
	const struct dc_link_settings *link_setting,
	const struct dc_link_training_overrides *overrides,
	struct link_training_settings *lt_settings)
{
	uint32_t lane;

	memset(lt_settings, '\0', sizeof(struct link_training_settings));

	/* Initialize link settings */
	lt_settings->link_settings.use_link_rate_set = link_setting->use_link_rate_set;
	lt_settings->link_settings.link_rate_set = link_setting->link_rate_set;

	if (link->preferred_link_setting.link_rate != LINK_RATE_UNKNOWN)
		lt_settings->link_settings.link_rate = link->preferred_link_setting.link_rate;
	else
		lt_settings->link_settings.link_rate = link_setting->link_rate;

	if (link->preferred_link_setting.lane_count != LANE_COUNT_UNKNOWN)
		lt_settings->link_settings.lane_count = link->preferred_link_setting.lane_count;
	else
		lt_settings->link_settings.lane_count = link_setting->lane_count;

	/*@todo[vdevulap] move SS to LS, should not be handled by displaypath*/

	/* TODO hard coded to SS for now
	 * lt_settings.link_settings.link_spread =
	 * dal_display_path_is_ss_supported(
	 * path_mode->display_path) ?
	 * LINK_SPREAD_05_DOWNSPREAD_30KHZ :
	 * LINK_SPREAD_DISABLED;
	 */
	/* Initialize link spread */
	if (link->dp_ss_off)
		lt_settings->link_settings.link_spread = LINK_SPREAD_DISABLED;
	else if (overrides->downspread != NULL)
		lt_settings->link_settings.link_spread
			= *overrides->downspread
			? LINK_SPREAD_05_DOWNSPREAD_30KHZ
			: LINK_SPREAD_DISABLED;
	else
		lt_settings->link_settings.link_spread = LINK_SPREAD_05_DOWNSPREAD_30KHZ;

	/* Initialize lane settings overrides */
	if (overrides->voltage_swing != NULL)
		lt_settings->voltage_swing = overrides->voltage_swing;

	if (overrides->pre_emphasis != NULL)
		lt_settings->pre_emphasis = overrides->pre_emphasis;

	if (overrides->post_cursor2 != NULL)
		lt_settings->post_cursor2 = overrides->post_cursor2;

	/* Initialize lane settings (VS/PE/PC2) */
	for (lane = 0; lane < LANE_COUNT_DP_MAX; lane++) {
		lt_settings->lane_settings[lane].VOLTAGE_SWING =
			lt_settings->voltage_swing != NULL ?
			*lt_settings->voltage_swing :
			VOLTAGE_SWING_LEVEL0;
		lt_settings->lane_settings[lane].PRE_EMPHASIS =
			lt_settings->pre_emphasis != NULL ?
			*lt_settings->pre_emphasis
			: PRE_EMPHASIS_DISABLED;
		lt_settings->lane_settings[lane].POST_CURSOR2 =
			lt_settings->post_cursor2 != NULL ?
			*lt_settings->post_cursor2
			: POST_CURSOR2_DISABLED;
	}

	/* Initialize training timings */
	if (overrides->cr_pattern_time != NULL)
		lt_settings->cr_pattern_time = *overrides->cr_pattern_time;
	else
		lt_settings->cr_pattern_time = get_training_aux_rd_interval(link, 100);

	if (overrides->eq_pattern_time != NULL)
		lt_settings->eq_pattern_time = *overrides->eq_pattern_time;
	else
		lt_settings->eq_pattern_time = get_training_aux_rd_interval(link, 400);

	if (overrides->pattern_for_eq != NULL)
		lt_settings->pattern_for_eq = *overrides->pattern_for_eq;
	else
		lt_settings->pattern_for_eq = get_supported_tp(link);

	if (overrides->enhanced_framing != NULL)
		lt_settings->enhanced_framing = *overrides->enhanced_framing;
	else
		lt_settings->enhanced_framing = 1;
}