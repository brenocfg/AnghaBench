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
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int dummy; } ;
struct crtc_position {unsigned int vertical_count; unsigned int nominal_vcount; } ;
struct core_freesync {int /*<<< orphan*/  dc; } ;

/* Variables and functions */
 struct core_freesync* MOD_FREESYNC_TO_CORE (struct mod_freesync*) ; 
 scalar_t__ dc_stream_get_crtc_position (int /*<<< orphan*/ ,struct dc_stream_state**,int,unsigned int*,unsigned int*) ; 

bool mod_freesync_get_v_position(struct mod_freesync *mod_freesync,
		struct dc_stream_state *stream,
		unsigned int *nom_v_pos,
		unsigned int *v_pos)
{
	struct core_freesync *core_freesync = NULL;
	struct crtc_position position;

	if (mod_freesync == NULL)
		return false;

	core_freesync = MOD_FREESYNC_TO_CORE(mod_freesync);

	if (dc_stream_get_crtc_position(core_freesync->dc, &stream, 1,
					&position.vertical_count,
					&position.nominal_vcount)) {

		*nom_v_pos = position.nominal_vcount;
		*v_pos = position.vertical_count;

		return true;
	}

	return false;
}