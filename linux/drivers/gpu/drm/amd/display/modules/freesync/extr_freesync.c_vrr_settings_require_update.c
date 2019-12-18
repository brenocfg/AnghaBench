#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ target_refresh_in_uhz; } ;
struct mod_vrr_params {scalar_t__ state; unsigned int min_refresh_in_uhz; unsigned int max_refresh_in_uhz; TYPE_1__ fixed; } ;
struct mod_freesync_config {scalar_t__ state; scalar_t__ min_refresh_in_uhz; } ;
struct core_freesync {int dummy; } ;

/* Variables and functions */
 scalar_t__ VRR_STATE_ACTIVE_FIXED ; 

__attribute__((used)) static bool vrr_settings_require_update(struct core_freesync *core_freesync,
		struct mod_freesync_config *in_config,
		unsigned int min_refresh_in_uhz,
		unsigned int max_refresh_in_uhz,
		struct mod_vrr_params *in_vrr)
{
	if (in_vrr->state != in_config->state) {
		return true;
	} else if (in_vrr->state == VRR_STATE_ACTIVE_FIXED &&
			in_vrr->fixed.target_refresh_in_uhz !=
					in_config->min_refresh_in_uhz) {
		return true;
	} else if (in_vrr->min_refresh_in_uhz != min_refresh_in_uhz) {
		return true;
	} else if (in_vrr->max_refresh_in_uhz != max_refresh_in_uhz) {
		return true;
	}

	return false;
}