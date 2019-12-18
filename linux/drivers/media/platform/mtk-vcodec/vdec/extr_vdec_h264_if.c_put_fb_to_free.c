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
typedef  scalar_t__ u64 ;
struct vdec_h264_inst {TYPE_1__* vsi; } ;
struct TYPE_5__ {scalar_t__ dma_addr; int /*<<< orphan*/  va; } ;
struct vdec_fb {TYPE_2__ base_y; } ;
struct h264_ring_fb_list {int count; size_t write_idx; TYPE_3__* fb_list; } ;
struct TYPE_6__ {scalar_t__ vdec_fb_va; } ;
struct TYPE_4__ {struct h264_ring_fb_list list_free; } ;

/* Variables and functions */
 int H264_MAX_FB_NUM ; 
 scalar_t__ check_list_validity (struct vdec_h264_inst*,int) ; 
 int /*<<< orphan*/  mtk_vcodec_debug (struct vdec_h264_inst*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mtk_vcodec_err (struct vdec_h264_inst*,char*) ; 

__attribute__((used)) static void put_fb_to_free(struct vdec_h264_inst *inst, struct vdec_fb *fb)
{
	struct h264_ring_fb_list *list;

	if (fb) {
		if (check_list_validity(inst, false))
			return;

		list = &inst->vsi->list_free;
		if (list->count == H264_MAX_FB_NUM) {
			mtk_vcodec_err(inst, "[FB] put fb free_list full");
			return;
		}

		mtk_vcodec_debug(inst, "[FB] put fb into free_list @(%p, %llx)",
				 fb->base_y.va, (u64)fb->base_y.dma_addr);

		list->fb_list[list->write_idx].vdec_fb_va = (u64)(uintptr_t)fb;
		list->write_idx = (list->write_idx == H264_MAX_FB_NUM - 1) ?
				  0 : list->write_idx + 1;
		list->count++;
	}
}