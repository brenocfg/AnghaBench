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
struct osd_info {int bits_per_pixel; int /*<<< orphan*/  display_byte_stride; int /*<<< orphan*/  video_buffer_size; int /*<<< orphan*/  video_pbase; } ;
struct ivtv {struct osd_info* osd_info; } ;
struct fb_fix_screeninfo {int xpanstep; int ypanstep; int /*<<< orphan*/  accel; int /*<<< orphan*/  line_length; scalar_t__ ywrapstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  IVTVFB_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  memset (struct fb_fix_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ivtvfb_get_fix(struct ivtv *itv, struct fb_fix_screeninfo *fix)
{
	struct osd_info *oi = itv->osd_info;

	IVTVFB_DEBUG_INFO("ivtvfb_get_fix\n");
	memset(fix, 0, sizeof(struct fb_fix_screeninfo));
	strscpy(fix->id, "cx23415 TV out", sizeof(fix->id));
	fix->smem_start = oi->video_pbase;
	fix->smem_len = oi->video_buffer_size;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->visual = (oi->bits_per_pixel == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->line_length = oi->display_byte_stride;
	fix->accel = FB_ACCEL_NONE;
	return 0;
}