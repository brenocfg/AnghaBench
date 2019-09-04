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
typedef  void* u32 ;
struct osd_info {void* video_rbase; int display_width; int display_height; } ;
struct ivtv_osd_coords {int max_offset; void* y; void* x; void* lines; void* pixel_stride; void* offset; } ;
struct ivtv {struct osd_info* osd_info; } ;

/* Variables and functions */
 int CX2341X_MBOX_MAX_DATA ; 
 int /*<<< orphan*/  CX2341X_OSD_GET_OSD_COORDS ; 
 int /*<<< orphan*/  ivtv_vapi_result (struct ivtv*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivtvfb_get_osd_coords(struct ivtv *itv,
				      struct ivtv_osd_coords *osd)
{
	struct osd_info *oi = itv->osd_info;
	u32 data[CX2341X_MBOX_MAX_DATA];

	ivtv_vapi_result(itv, data, CX2341X_OSD_GET_OSD_COORDS, 0);

	osd->offset = data[0] - oi->video_rbase;
	osd->max_offset = oi->display_width * oi->display_height * 4;
	osd->pixel_stride = data[1];
	osd->lines = data[2];
	osd->x = data[3];
	osd->y = data[4];
	return 0;
}