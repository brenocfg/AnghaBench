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
struct videomode {int hback_porch; int hfront_porch; int hsync_len; int vback_porch; int vfront_porch; int vsync_len; int flags; } ;
struct hdmi_video_format {int y_res; int x_res; int /*<<< orphan*/  packing_mode; } ;
struct TYPE_2__ {int vactive; int hactive; int hback_porch; int hfront_porch; int hsync_len; int vback_porch; int vfront_porch; int vsync_len; int flags; } ;
struct hdmi_config {TYPE_1__ vm; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DOUBLECLK ; 
 int DISPLAY_FLAGS_INTERLACED ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  HDMI_PACK_10b_RGB_YUV444 ; 

void hdmi_wp_init_vid_fmt_timings(struct hdmi_video_format *video_fmt,
		struct videomode *vm, const struct hdmi_config *param)
{
	DSSDBG("Enter hdmi_wp_video_init_format\n");

	video_fmt->packing_mode = HDMI_PACK_10b_RGB_YUV444;
	video_fmt->y_res = param->vm.vactive;
	video_fmt->x_res = param->vm.hactive;

	vm->hback_porch = param->vm.hback_porch;
	vm->hfront_porch = param->vm.hfront_porch;
	vm->hsync_len = param->vm.hsync_len;
	vm->vback_porch = param->vm.vback_porch;
	vm->vfront_porch = param->vm.vfront_porch;
	vm->vsync_len = param->vm.vsync_len;

	vm->flags = param->vm.flags;

	if (param->vm.flags & DISPLAY_FLAGS_INTERLACED) {
		video_fmt->y_res /= 2;
		vm->vback_porch /= 2;
		vm->vfront_porch /= 2;
		vm->vsync_len /= 2;
	}

	if (param->vm.flags & DISPLAY_FLAGS_DOUBLECLK) {
		video_fmt->x_res *= 2;
		vm->hfront_porch *= 2;
		vm->hsync_len *= 2;
		vm->hback_porch *= 2;
	}
}