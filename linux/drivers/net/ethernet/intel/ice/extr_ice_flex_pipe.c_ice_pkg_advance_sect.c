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
struct ice_seg {int dummy; } ;
struct ice_pkg_enum {scalar_t__ sect_idx; TYPE_1__* buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  section_count; } ;

/* Variables and functions */
 TYPE_1__* ice_pkg_enum_buf (struct ice_seg*,struct ice_pkg_enum*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ice_pkg_advance_sect(struct ice_seg *ice_seg, struct ice_pkg_enum *state)
{
	if (!ice_seg && !state->buf)
		return false;

	if (!ice_seg && state->buf)
		if (++state->sect_idx < le16_to_cpu(state->buf->section_count))
			return true;

	state->buf = ice_pkg_enum_buf(ice_seg, state);
	if (!state->buf)
		return false;

	/* start of new buffer, reset section index */
	state->sect_idx = 0;
	return true;
}