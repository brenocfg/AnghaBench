#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct link_training_settings {int dummy; } ;
struct dc_link_settings {int dummy; } ;
struct TYPE_8__ {int* fec_enable; } ;
struct dc_link {TYPE_3__* ctx; TYPE_4__ preferred_training_settings; } ;
typedef  enum link_training_result { ____Placeholder_link_training_result } link_training_result ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_5__ {int /*<<< orphan*/  ltFailCount; } ;
struct TYPE_6__ {TYPE_1__ debug_data; } ;

/* Variables and functions */
 int LINK_TRAINING_SUCCESS ; 
 int /*<<< orphan*/  dp_set_fec_ready (struct dc_link*,int) ; 
 int /*<<< orphan*/  dpcd_set_link_settings (struct dc_link*,struct link_training_settings*) ; 
 int /*<<< orphan*/  initialize_training_settings (struct dc_link*,struct dc_link_settings const*,TYPE_4__*,struct link_training_settings*) ; 
 int perform_channel_equalization_sequence (struct dc_link*,struct link_training_settings*) ; 
 int perform_clock_recovery_sequence (struct dc_link*,struct link_training_settings*) ; 
 int perform_link_training_int (struct dc_link*,struct link_training_settings*,int) ; 
 int /*<<< orphan*/  print_status_message (struct dc_link*,struct link_training_settings*,int) ; 

enum link_training_result dc_link_dp_perform_link_training(
	struct dc_link *link,
	const struct dc_link_settings *link_setting,
	bool skip_video_pattern)
{
	enum link_training_result status = LINK_TRAINING_SUCCESS;
	struct link_training_settings lt_settings;
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	bool fec_enable;
#endif

	initialize_training_settings(
			link,
			link_setting,
			&link->preferred_training_settings,
			&lt_settings);

	/* 1. set link rate, lane count and spread. */
	dpcd_set_link_settings(link, &lt_settings);

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	if (link->preferred_training_settings.fec_enable != NULL)
		fec_enable = *link->preferred_training_settings.fec_enable;
	else
		fec_enable = true;

	dp_set_fec_ready(link, fec_enable);
#endif


	/* 2. perform link training (set link training done
	 *  to false is done as well)
	 */
	status = perform_clock_recovery_sequence(link, &lt_settings);
	if (status == LINK_TRAINING_SUCCESS) {
		status = perform_channel_equalization_sequence(link,
				&lt_settings);
	}

	if ((status == LINK_TRAINING_SUCCESS) || !skip_video_pattern) {
		status = perform_link_training_int(link,
				&lt_settings,
				status);
	}

	/* 6. print status message*/
	print_status_message(link, &lt_settings, status);

	if (status != LINK_TRAINING_SUCCESS)
		link->ctx->dc->debug_data.ltFailCount++;

	return status;
}