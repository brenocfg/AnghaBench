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
struct vdec_vp9_inst {int dummy; } ;
struct vdec_fb {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ST_DISPLAY ; 
 struct vdec_fb* vp9_rm_from_fb_disp_list (struct vdec_vp9_inst*) ; 

__attribute__((used)) static void get_disp_fb(struct vdec_vp9_inst *inst, struct vdec_fb **out_fb)
{

	*out_fb = vp9_rm_from_fb_disp_list(inst);
	if (*out_fb)
		(*out_fb)->status |= FB_ST_DISPLAY;
}