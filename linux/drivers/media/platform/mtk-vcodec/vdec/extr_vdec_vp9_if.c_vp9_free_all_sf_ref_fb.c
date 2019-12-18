#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vdec_vp9_vsi {TYPE_3__* sf_ref_fb; } ;
struct vdec_vp9_inst {int /*<<< orphan*/  ctx; struct vdec_vp9_vsi* vsi; } ;
struct TYPE_5__ {scalar_t__ va; } ;
struct TYPE_4__ {TYPE_2__ base_c; TYPE_2__ base_y; } ;
struct TYPE_6__ {scalar_t__ used; TYPE_1__ fb; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  mtk_vcodec_mem_free (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void vp9_free_all_sf_ref_fb(struct vdec_vp9_inst *inst)
{
	int i;
	struct vdec_vp9_vsi *vsi = inst->vsi;

	for (i = 0; i < ARRAY_SIZE(vsi->sf_ref_fb); i++) {
		if (vsi->sf_ref_fb[i].fb.base_y.va) {
			mtk_vcodec_mem_free(inst->ctx,
				&vsi->sf_ref_fb[i].fb.base_y);
			mtk_vcodec_mem_free(inst->ctx,
				&vsi->sf_ref_fb[i].fb.base_c);
			vsi->sf_ref_fb[i].used = 0;
		}
	}
}