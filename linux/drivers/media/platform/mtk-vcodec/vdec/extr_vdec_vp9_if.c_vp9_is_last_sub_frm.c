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
struct vdec_vp9_vsi {scalar_t__ sf_frm_cnt; scalar_t__ sf_frm_idx; } ;
struct vdec_vp9_inst {struct vdec_vp9_vsi* vsi; } ;

/* Variables and functions */

__attribute__((used)) static bool vp9_is_last_sub_frm(struct vdec_vp9_inst *inst)
{
	struct vdec_vp9_vsi *vsi = inst->vsi;

	if (vsi->sf_frm_cnt <= 0 || vsi->sf_frm_idx == vsi->sf_frm_cnt)
		return true;

	return false;
}