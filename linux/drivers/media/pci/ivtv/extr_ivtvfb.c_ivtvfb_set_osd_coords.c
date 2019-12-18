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
struct osd_info {int display_width; int display_byte_stride; int bytes_per_pixel; scalar_t__ video_rbase; int /*<<< orphan*/  set_osd_coords_y; int /*<<< orphan*/  set_osd_coords_x; } ;
struct ivtv_osd_coords {int pixel_stride; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  lines; scalar_t__ offset; } ;
struct ivtv {struct osd_info* osd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_OSD_COORDS ; 
 int ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivtvfb_set_osd_coords(struct ivtv *itv, const struct ivtv_osd_coords *osd)
{
	struct osd_info *oi = itv->osd_info;

	oi->display_width = osd->pixel_stride;
	oi->display_byte_stride = osd->pixel_stride * oi->bytes_per_pixel;
	oi->set_osd_coords_x += osd->x;
	oi->set_osd_coords_y = osd->y;

	return ivtv_vapi(itv, CX2341X_OSD_SET_OSD_COORDS, 5,
			osd->offset + oi->video_rbase,
			osd->pixel_stride,
			osd->lines, osd->x, osd->y);
}