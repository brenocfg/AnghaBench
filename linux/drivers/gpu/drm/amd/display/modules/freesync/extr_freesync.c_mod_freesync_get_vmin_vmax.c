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
struct mod_freesync {int dummy; } ;
struct TYPE_2__ {unsigned int v_total_min; unsigned int v_total_max; } ;
struct dc_stream_state {TYPE_1__ adjust; } ;

/* Variables and functions */

bool mod_freesync_get_vmin_vmax(struct mod_freesync *mod_freesync,
		const struct dc_stream_state *stream,
		unsigned int *vmin,
		unsigned int *vmax)
{
	*vmin = stream->adjust.v_total_min;
	*vmax = stream->adjust.v_total_max;

	return true;
}