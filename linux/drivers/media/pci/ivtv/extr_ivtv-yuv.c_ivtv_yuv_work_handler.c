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
typedef  int u32 ;
struct yuv_frame_info {int vis_w; int /*<<< orphan*/  vis_h; scalar_t__ pan_y; scalar_t__ pan_x; } ;
struct yuv_playback_info {int update_frame; int osd_vis_w; struct yuv_frame_info old_frame_info; int /*<<< orphan*/  decode_height; int /*<<< orphan*/  osd_vis_h; scalar_t__ osd_y_pan; scalar_t__ osd_x_pan; scalar_t__ track_osd; struct yuv_frame_info* new_frame_info; } ;
struct ivtv {struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*,int) ; 
 int IVTV_YUV_UPDATE_HORIZONTAL ; 
 int IVTV_YUV_UPDATE_INVALID ; 
 int IVTV_YUV_UPDATE_VERTICAL ; 
 int /*<<< orphan*/  ivtv_yuv_handle_horizontal (struct ivtv*,struct yuv_frame_info*) ; 
 int /*<<< orphan*/  ivtv_yuv_handle_vertical (struct ivtv*,struct yuv_frame_info*) ; 
 int ivtv_yuv_window_setup (struct ivtv*,struct yuv_frame_info*) ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

void ivtv_yuv_work_handler(struct ivtv *itv)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	struct yuv_frame_info f;
	int frame = yi->update_frame;
	u32 yuv_update;

	IVTV_DEBUG_YUV("Update yuv registers for frame %d\n", frame);
	f = yi->new_frame_info[frame];

	if (yi->track_osd) {
		/* Snapshot the osd pan info */
		f.pan_x = yi->osd_x_pan;
		f.pan_y = yi->osd_y_pan;
		f.vis_w = yi->osd_vis_w;
		f.vis_h = yi->osd_vis_h;
	} else {
		/* Not tracking the osd, so assume full screen */
		f.pan_x = 0;
		f.pan_y = 0;
		f.vis_w = 720;
		f.vis_h = yi->decode_height;
	}

	/* Calculate the display window coordinates. Exit if nothing left */
	if (!(yuv_update = ivtv_yuv_window_setup(itv, &f)))
		return;

	if (yuv_update & IVTV_YUV_UPDATE_INVALID) {
		write_reg(0x01008080, 0x2898);
	} else if (yuv_update) {
		write_reg(0x00108080, 0x2898);

		if (yuv_update & IVTV_YUV_UPDATE_HORIZONTAL)
			ivtv_yuv_handle_horizontal(itv, &f);

		if (yuv_update & IVTV_YUV_UPDATE_VERTICAL)
			ivtv_yuv_handle_vertical(itv, &f);
	}
	yi->old_frame_info = f;
}