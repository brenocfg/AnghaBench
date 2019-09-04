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
struct vdec_vp9_vsi {TYPE_1__* sf_ref_fb; } ;
struct vdec_vp9_inst {struct vdec_vp9_vsi* vsi; } ;
struct vdec_fb {int dummy; } ;
struct TYPE_2__ {struct vdec_fb fb; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 

__attribute__((used)) static bool vp9_is_sf_ref_fb(struct vdec_vp9_inst *inst, struct vdec_fb *fb)
{
	int i;
	struct vdec_vp9_vsi *vsi = inst->vsi;

	for (i = 0; i < ARRAY_SIZE(vsi->sf_ref_fb); i++) {
		if (fb == &vsi->sf_ref_fb[i].fb)
			return true;
	}
	return false;
}