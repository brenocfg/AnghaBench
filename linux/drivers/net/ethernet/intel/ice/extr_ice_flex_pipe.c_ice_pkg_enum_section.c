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
typedef  void u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct ice_seg {int dummy; } ;
struct ice_pkg_enum {size_t sect_idx; void* sect; TYPE_2__* buf; int /*<<< orphan*/  sect_type; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__* section_entry; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ ICE_MAX_S_OFF ; 
 scalar_t__ ICE_MAX_S_SZ ; 
 scalar_t__ ICE_MIN_S_OFF ; 
 scalar_t__ ICE_MIN_S_SZ ; 
 scalar_t__ ICE_PKG_BUF_SIZE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_pkg_advance_sect (struct ice_seg*,struct ice_pkg_enum*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static void *
ice_pkg_enum_section(struct ice_seg *ice_seg, struct ice_pkg_enum *state,
		     u32 sect_type)
{
	u16 offset, size;

	if (ice_seg)
		state->type = sect_type;

	if (!ice_pkg_advance_sect(ice_seg, state))
		return NULL;

	/* scan for next matching section */
	while (state->buf->section_entry[state->sect_idx].type !=
	       cpu_to_le32(state->type))
		if (!ice_pkg_advance_sect(NULL, state))
			return NULL;

	/* validate section */
	offset = le16_to_cpu(state->buf->section_entry[state->sect_idx].offset);
	if (offset < ICE_MIN_S_OFF || offset > ICE_MAX_S_OFF)
		return NULL;

	size = le16_to_cpu(state->buf->section_entry[state->sect_idx].size);
	if (size < ICE_MIN_S_SZ || size > ICE_MAX_S_SZ)
		return NULL;

	/* make sure the section fits in the buffer */
	if (offset + size > ICE_PKG_BUF_SIZE)
		return NULL;

	state->sect_type =
		le32_to_cpu(state->buf->section_entry[state->sect_idx].type);

	/* calc pointer to this section */
	state->sect = ((u8 *)state->buf) +
		le16_to_cpu(state->buf->section_entry[state->sect_idx].offset);

	return state->sect;
}