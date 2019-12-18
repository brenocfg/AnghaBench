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
struct TYPE_3__ {int /*<<< orphan*/  link_rate; int /*<<< orphan*/  lane_count; } ;
struct dc_link {scalar_t__ connector_signal; TYPE_1__ verified_link_cap; } ;
struct TYPE_4__ {int override_edid; } ;
struct amdgpu_dm_connector {TYPE_2__ base; scalar_t__ dc_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  LANE_COUNT_FOUR ; 
 int /*<<< orphan*/  LINK_RATE_HIGH2 ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  create_eml_sink (struct amdgpu_dm_connector*) ; 

__attribute__((used)) static void handle_edid_mgmt(struct amdgpu_dm_connector *aconnector)
{
	struct dc_link *link = (struct dc_link *)aconnector->dc_link;

	/*
	 * In case of headless boot with force on for DP managed connector
	 * Those settings have to be != 0 to get initial modeset
	 */
	if (link->connector_signal == SIGNAL_TYPE_DISPLAY_PORT) {
		link->verified_link_cap.lane_count = LANE_COUNT_FOUR;
		link->verified_link_cap.link_rate = LINK_RATE_HIGH2;
	}


	aconnector->base.override_edid = true;
	create_eml_sink(aconnector);
}