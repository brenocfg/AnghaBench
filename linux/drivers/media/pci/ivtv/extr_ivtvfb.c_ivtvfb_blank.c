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
struct ivtv {TYPE_1__* osd_info; } ;
struct fb_info {scalar_t__ par; } ;
struct TYPE_2__ {int blank_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_OSD_SET_STATE ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  IVTVFB_DEBUG_INFO (char*,int) ; 
 int /*<<< orphan*/  IVTV_HW_SAA7127 ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ivtv_vapi (struct ivtv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int ivtvfb_blank(int blank_mode, struct fb_info *info)
{
	struct ivtv *itv = (struct ivtv *)info->par;

	IVTVFB_DEBUG_INFO("Set blanking mode : %d\n", blank_mode);
	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 1);
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 1);
		break;
	case FB_BLANK_NORMAL:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_VSYNC_SUSPEND:
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 0);
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 1);
		break;
	case FB_BLANK_POWERDOWN:
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 0);
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 0);
		break;
	}
	itv->osd_info->blank_cur = blank_mode;
	return 0;
}