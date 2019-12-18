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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dp {TYPE_2__* attached_connector; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct TYPE_3__ {struct drm_display_mode* fixed_mode; } ;
struct TYPE_4__ {TYPE_1__ panel; } ;

/* Variables and functions */
 int intel_dp_link_required (int /*<<< orphan*/ ,int) ; 
 int intel_dp_max_data_rate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_dp_can_link_train_fallback_for_edp(struct intel_dp *intel_dp,
						     int link_rate,
						     u8 lane_count)
{
	const struct drm_display_mode *fixed_mode =
		intel_dp->attached_connector->panel.fixed_mode;
	int mode_rate, max_rate;

	mode_rate = intel_dp_link_required(fixed_mode->clock, 18);
	max_rate = intel_dp_max_data_rate(link_rate, lane_count);
	if (mode_rate > max_rate)
		return false;

	return true;
}