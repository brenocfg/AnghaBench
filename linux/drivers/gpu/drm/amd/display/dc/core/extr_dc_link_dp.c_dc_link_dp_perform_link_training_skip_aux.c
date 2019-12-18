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
struct link_training_settings {int pattern_for_eq; int /*<<< orphan*/  eq_pattern_time; int /*<<< orphan*/  cr_pattern_time; } ;
struct dc_link_settings {int dummy; } ;
struct dc_link {int /*<<< orphan*/  preferred_training_settings; } ;
typedef  enum dc_dp_training_pattern { ____Placeholder_dc_dp_training_pattern } dc_dp_training_pattern ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TEST_PATTERN_VIDEO_MODE ; 
 int DP_TRAINING_PATTERN_SEQUENCE_1 ; 
 int /*<<< orphan*/  LINK_TRAINING_SUCCESS ; 
 int /*<<< orphan*/  dp_set_hw_lane_settings (struct dc_link*,struct link_training_settings*) ; 
 int /*<<< orphan*/  dp_set_hw_test_pattern (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_set_hw_training_pattern (struct dc_link*,int) ; 
 int /*<<< orphan*/  initialize_training_settings (struct dc_link*,struct dc_link_settings const*,int /*<<< orphan*/ *,struct link_training_settings*) ; 
 int /*<<< orphan*/  print_status_message (struct dc_link*,struct link_training_settings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_training_aux_rd_interval (struct dc_link*,int /*<<< orphan*/ ) ; 

bool dc_link_dp_perform_link_training_skip_aux(
	struct dc_link *link,
	const struct dc_link_settings *link_setting)
{
	struct link_training_settings lt_settings;
	enum dc_dp_training_pattern pattern_for_cr = DP_TRAINING_PATTERN_SEQUENCE_1;

	initialize_training_settings(
			link,
			link_setting,
			&link->preferred_training_settings,
			&lt_settings);

	/* 1. Perform_clock_recovery_sequence. */

	/* transmit training pattern for clock recovery */
	dp_set_hw_training_pattern(link, pattern_for_cr);

	/* call HWSS to set lane settings*/
	dp_set_hw_lane_settings(link, &lt_settings);

	/* wait receiver to lock-on*/
	wait_for_training_aux_rd_interval(link, lt_settings.cr_pattern_time);

	/* 2. Perform_channel_equalization_sequence. */

	/* transmit training pattern for channel equalization. */
	dp_set_hw_training_pattern(link, lt_settings.pattern_for_eq);

	/* call HWSS to set lane settings*/
	dp_set_hw_lane_settings(link, &lt_settings);

	/* wait receiver to lock-on. */
	wait_for_training_aux_rd_interval(link, lt_settings.eq_pattern_time);

	/* 3. Perform_link_training_int. */

	/* Mainlink output idle pattern. */
	dp_set_hw_test_pattern(link, DP_TEST_PATTERN_VIDEO_MODE, NULL, 0);

	print_status_message(link, &lt_settings, LINK_TRAINING_SUCCESS);

	return true;
}