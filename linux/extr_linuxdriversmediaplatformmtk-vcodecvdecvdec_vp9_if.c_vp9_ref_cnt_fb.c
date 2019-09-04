#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vdec_vp9_vsi {TYPE_3__* frm_bufs; } ;
struct vdec_vp9_inst {struct vdec_vp9_vsi* vsi; } ;
struct vdec_fb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  va; } ;
struct TYPE_9__ {TYPE_1__ base_y; } ;
struct TYPE_7__ {TYPE_4__* fb; } ;
struct TYPE_8__ {scalar_t__ ref_cnt; TYPE_2__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  vp9_add_to_fb_free_list (struct vdec_vp9_inst*,struct vdec_fb*) ; 
 int /*<<< orphan*/  vp9_free_sf_ref_fb (TYPE_4__*) ; 
 int /*<<< orphan*/  vp9_is_sf_ref_fb (struct vdec_vp9_inst*,TYPE_4__*) ; 
 struct vdec_fb* vp9_rm_from_fb_use_list (struct vdec_vp9_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp9_ref_cnt_fb(struct vdec_vp9_inst *inst, int *idx,
			   int new_idx)
{
	struct vdec_vp9_vsi *vsi = inst->vsi;
	int ref_idx = *idx;

	if (ref_idx >= 0 && vsi->frm_bufs[ref_idx].ref_cnt > 0) {
		vsi->frm_bufs[ref_idx].ref_cnt--;

		if (vsi->frm_bufs[ref_idx].ref_cnt == 0) {
			if (!vp9_is_sf_ref_fb(inst,
					      vsi->frm_bufs[ref_idx].buf.fb)) {
				struct vdec_fb *fb;

				fb = vp9_rm_from_fb_use_list(inst,
				     vsi->frm_bufs[ref_idx].buf.fb->base_y.va);
				vp9_add_to_fb_free_list(inst, fb);
			} else
				vp9_free_sf_ref_fb(
					vsi->frm_bufs[ref_idx].buf.fb);
		}
	}

	*idx = new_idx;
	vsi->frm_bufs[new_idx].ref_cnt++;
}