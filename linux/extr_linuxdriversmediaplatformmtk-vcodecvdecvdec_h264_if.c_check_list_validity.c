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
struct vdec_h264_inst {TYPE_1__* vsi; } ;
struct h264_ring_fb_list {scalar_t__ count; scalar_t__ read_idx; scalar_t__ write_idx; } ;
struct TYPE_2__ {struct h264_ring_fb_list list_free; struct h264_ring_fb_list list_disp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ H264_MAX_FB_NUM ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_h264_inst*,char*,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int check_list_validity(struct vdec_h264_inst *inst, bool disp_list)
{
	struct h264_ring_fb_list *list;

	list = disp_list ? &inst->vsi->list_disp : &inst->vsi->list_free;

	if (list->count > H264_MAX_FB_NUM ||
	    list->read_idx >= H264_MAX_FB_NUM ||
	    list->write_idx >= H264_MAX_FB_NUM) {
		mtk_vcodec_err(inst, "%s list err: cnt=%d r_idx=%d w_idx=%d",
			       disp_list ? "disp" : "free", list->count,
			       list->read_idx, list->write_idx);
		return -EINVAL;
	}

	return 0;
}