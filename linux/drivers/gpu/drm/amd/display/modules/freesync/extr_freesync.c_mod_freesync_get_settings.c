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
struct TYPE_4__ {unsigned int mid_point_in_us; unsigned int frames_to_insert; unsigned int inserted_duration_in_us; } ;
struct TYPE_3__ {unsigned int v_total_min; unsigned int v_total_max; } ;
struct mod_vrr_params {TYPE_2__ btr; TYPE_1__ adjust; scalar_t__ supported; } ;
struct mod_freesync {int dummy; } ;
struct core_freesync {int dummy; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 

void mod_freesync_get_settings(struct mod_freesync *mod_freesync,
		const struct mod_vrr_params *vrr,
		unsigned int *v_total_min, unsigned int *v_total_max,
		unsigned int *event_triggers,
		unsigned int *window_min, unsigned int *window_max,
		unsigned int *lfc_mid_point_in_us,
		unsigned int *inserted_frames,
		unsigned int *inserted_duration_in_us)
{
	struct core_freesync *core_freesync = NULL;

	if (mod_freesync == NULL)
		return;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	if (vrr->supported) {
		*v_total_min = vrr->adjust.v_total_min;
		*v_total_max = vrr->adjust.v_total_max;
		*event_triggers = 0;
		*lfc_mid_point_in_us = vrr->btr.mid_point_in_us;
		*inserted_frames = vrr->btr.frames_to_insert;
		*inserted_duration_in_us = vrr->btr.inserted_duration_in_us;
	}
}