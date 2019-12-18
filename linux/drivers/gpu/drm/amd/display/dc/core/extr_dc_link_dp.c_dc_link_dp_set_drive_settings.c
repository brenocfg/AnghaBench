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
struct dc_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dp_set_hw_lane_settings (struct dc_link*,struct link_training_settings*) ; 
 int /*<<< orphan*/  dpcd_set_lane_settings (struct dc_link*,struct link_training_settings*) ; 

void dc_link_dp_set_drive_settings(
	struct dc_link *link,
	struct link_training_settings *lt_settings)
{
	/* program ASIC PHY settings*/
	dp_set_hw_lane_settings(link, lt_settings);

	/* Notify DP sink the PHY settings from source */
	dpcd_set_lane_settings(link, lt_settings);
}