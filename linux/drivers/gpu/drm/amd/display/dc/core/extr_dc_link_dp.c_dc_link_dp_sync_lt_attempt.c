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
struct link_training_settings {int dummy; } ;
struct dc_link_training_overrides {scalar_t__* alternate_scrambler_reset; scalar_t__* fec_enable; int /*<<< orphan*/ * mst_enable; } ;
struct dc_link_settings {int dummy; } ;
struct dc_link {int /*<<< orphan*/  connector_signal; } ;
typedef  enum link_training_result { ____Placeholder_link_training_result } link_training_result ;
typedef  enum dp_panel_mode { ____Placeholder_dp_panel_mode } dp_panel_mode ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;

/* Variables and functions */
 int CLOCK_SOURCE_ID_EXTERNAL ; 
 int DP_PANEL_MODE_DEFAULT ; 
 int DP_PANEL_MODE_EDP ; 
 int LINK_TRAINING_SUCCESS ; 
 int /*<<< orphan*/  dp_disable_link_phy (struct dc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_enable_link_phy (struct dc_link*,int /*<<< orphan*/ ,int,struct dc_link_settings*) ; 
 int dp_get_panel_mode (struct dc_link*) ; 
 int /*<<< orphan*/  dp_set_fec_ready (struct dc_link*,int) ; 
 int /*<<< orphan*/  dp_set_panel_mode (struct dc_link*,int) ; 
 int /*<<< orphan*/  dpcd_set_link_settings (struct dc_link*,struct link_training_settings*) ; 
 int get_clock_source_id (struct dc_link*) ; 
 int /*<<< orphan*/  initialize_training_settings (struct dc_link*,struct dc_link_settings*,struct dc_link_training_overrides*,struct link_training_settings*) ; 
 int perform_channel_equalization_sequence (struct dc_link*,struct link_training_settings*) ; 
 int perform_clock_recovery_sequence (struct dc_link*,struct link_training_settings*) ; 
 int /*<<< orphan*/  print_status_message (struct dc_link*,struct link_training_settings*,int) ; 
 int /*<<< orphan*/  set_dp_mst_mode (struct dc_link*,int /*<<< orphan*/ ) ; 

enum link_training_result dc_link_dp_sync_lt_attempt(
    struct dc_link *link,
    struct dc_link_settings *link_settings,
    struct dc_link_training_overrides *lt_overrides)
{
	struct link_training_settings lt_settings;
	enum link_training_result lt_status = LINK_TRAINING_SUCCESS;
	enum dp_panel_mode panel_mode = DP_PANEL_MODE_DEFAULT;
	enum clock_source_id dp_cs_id = CLOCK_SOURCE_ID_EXTERNAL;
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	bool fec_enable = false;
#endif

	initialize_training_settings(
		link,
		link_settings,
		lt_overrides,
		&lt_settings);

	/* Setup MST Mode */
	if (lt_overrides->mst_enable)
		set_dp_mst_mode(link, *lt_overrides->mst_enable);

	/* Disable link */
	dp_disable_link_phy(link, link->connector_signal);

	/* Enable link */
	dp_cs_id = get_clock_source_id(link);
	dp_enable_link_phy(link, link->connector_signal,
		dp_cs_id, link_settings);

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	/* Set FEC enable */
	fec_enable = lt_overrides->fec_enable && *lt_overrides->fec_enable;
	dp_set_fec_ready(link, fec_enable);
#endif

	if (lt_overrides->alternate_scrambler_reset) {
		if (*lt_overrides->alternate_scrambler_reset)
			panel_mode = DP_PANEL_MODE_EDP;
		else
			panel_mode = DP_PANEL_MODE_DEFAULT;
	} else
		panel_mode = dp_get_panel_mode(link);

	dp_set_panel_mode(link, panel_mode);

	/* Attempt to train with given link training settings */

	/* Set link rate, lane count and spread. */
	dpcd_set_link_settings(link, &lt_settings);

	/* 2. perform link training (set link training done
	 *  to false is done as well)
	 */
	lt_status = perform_clock_recovery_sequence(link, &lt_settings);
	if (lt_status == LINK_TRAINING_SUCCESS) {
		lt_status = perform_channel_equalization_sequence(link,
						&lt_settings);
	}

	/* 3. Sync LT must skip TRAINING_PATTERN_SET:0 (video pattern)*/
	/* 4. print status message*/
	print_status_message(link, &lt_settings, lt_status);

	return lt_status;
}