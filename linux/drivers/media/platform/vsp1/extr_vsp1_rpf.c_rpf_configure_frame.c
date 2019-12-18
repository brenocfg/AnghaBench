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
struct vsp1_rwpf {int alpha; int mult_alpha; } ;
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_RPF_MULT_ALPHA ; 
 int VI6_RPF_MULT_ALPHA_RATIO_SHIFT ; 
 int /*<<< orphan*/  VI6_RPF_VRTCOL_SET ; 
 int VI6_RPF_VRTCOL_SET_LAYA_SHIFT ; 
 struct vsp1_rwpf* to_rwpf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_pipeline_propagate_alpha (struct vsp1_pipeline*,struct vsp1_dl_body*,int) ; 
 int /*<<< orphan*/  vsp1_rpf_write (struct vsp1_rwpf*,struct vsp1_dl_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rpf_configure_frame(struct vsp1_entity *entity,
				struct vsp1_pipeline *pipe,
				struct vsp1_dl_list *dl,
				struct vsp1_dl_body *dlb)
{
	struct vsp1_rwpf *rpf = to_rwpf(&entity->subdev);

	vsp1_rpf_write(rpf, dlb, VI6_RPF_VRTCOL_SET,
		       rpf->alpha << VI6_RPF_VRTCOL_SET_LAYA_SHIFT);
	vsp1_rpf_write(rpf, dlb, VI6_RPF_MULT_ALPHA, rpf->mult_alpha |
		       (rpf->alpha << VI6_RPF_MULT_ALPHA_RATIO_SHIFT));

	vsp1_pipeline_propagate_alpha(pipe, dlb, rpf->alpha);
}