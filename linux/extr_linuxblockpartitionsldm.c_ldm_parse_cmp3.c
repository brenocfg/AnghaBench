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
typedef  int u8 ;
struct vblk_comp {int type; void* chunksize; void* parent_id; void* children; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct vblk_comp comp; } ;
struct vblk {TYPE_1__ vblk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int const VBLK_FLAG_COMP_STRIPE ; 
 scalar_t__ VBLK_SIZE_CMP3 ; 
 int get_unaligned_be32 (int const*) ; 
 void* ldm_get_vnum (int const*) ; 
 int /*<<< orphan*/  ldm_get_vstr (int const*,int /*<<< orphan*/ ,int) ; 
 int ldm_relative (int const*,int,int,int) ; 

__attribute__((used)) static bool ldm_parse_cmp3 (const u8 *buffer, int buflen, struct vblk *vb)
{
	int r_objid, r_name, r_vstate, r_child, r_parent, r_stripe, r_cols, len;
	struct vblk_comp *comp;

	BUG_ON (!buffer || !vb);

	r_objid  = ldm_relative (buffer, buflen, 0x18, 0);
	r_name   = ldm_relative (buffer, buflen, 0x18, r_objid);
	r_vstate = ldm_relative (buffer, buflen, 0x18, r_name);
	r_child  = ldm_relative (buffer, buflen, 0x1D, r_vstate);
	r_parent = ldm_relative (buffer, buflen, 0x2D, r_child);

	if (buffer[0x12] & VBLK_FLAG_COMP_STRIPE) {
		r_stripe = ldm_relative (buffer, buflen, 0x2E, r_parent);
		r_cols   = ldm_relative (buffer, buflen, 0x2E, r_stripe);
		len = r_cols;
	} else {
		r_stripe = 0;
		r_cols   = 0;
		len = r_parent;
	}
	if (len < 0)
		return false;

	len += VBLK_SIZE_CMP3;
	if (len != get_unaligned_be32(buffer + 0x14))
		return false;

	comp = &vb->vblk.comp;
	ldm_get_vstr (buffer + 0x18 + r_name, comp->state,
		sizeof (comp->state));
	comp->type      = buffer[0x18 + r_vstate];
	comp->children  = ldm_get_vnum (buffer + 0x1D + r_vstate);
	comp->parent_id = ldm_get_vnum (buffer + 0x2D + r_child);
	comp->chunksize = r_stripe ? ldm_get_vnum (buffer+r_parent+0x2E) : 0;

	return true;
}