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
struct dc_link_training_overrides {int dummy; } ;
struct dc_link_settings {int /*<<< orphan*/  link_rate; int /*<<< orphan*/  lane_count; } ;
struct dc_link {struct dc_link_settings preferred_link_setting; struct dc_link_training_overrides preferred_training_settings; } ;
struct dc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LANE_COUNT_UNKNOWN ; 
 int /*<<< orphan*/  LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  dc_link_set_preferred_link_settings (struct dc*,struct dc_link_settings*,struct dc_link*) ; 
 int /*<<< orphan*/  memset (struct dc_link_training_overrides*,int /*<<< orphan*/ ,int) ; 

void dc_link_set_preferred_training_settings(struct dc *dc,
						 struct dc_link_settings *link_setting,
						 struct dc_link_training_overrides *lt_overrides,
						 struct dc_link *link,
						 bool skip_immediate_retrain)
{
	if (lt_overrides != NULL)
		link->preferred_training_settings = *lt_overrides;
	else
		memset(&link->preferred_training_settings, 0, sizeof(link->preferred_training_settings));

	if (link_setting != NULL) {
		link->preferred_link_setting = *link_setting;
	} else {
		link->preferred_link_setting.lane_count = LANE_COUNT_UNKNOWN;
		link->preferred_link_setting.link_rate = LINK_RATE_UNKNOWN;
	}

	/* Retrain now, or wait until next stream update to apply */
	if (skip_immediate_retrain == false)
		dc_link_set_preferred_link_settings(dc, &link->preferred_link_setting, link);
}