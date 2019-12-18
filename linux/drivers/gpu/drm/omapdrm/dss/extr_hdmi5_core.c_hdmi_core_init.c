#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hfront_porch; int hback_porch; int hsync_len; int vsync_len; int vfront_porch; int vback_porch; int flags; int vactive; int hactive; } ;
struct TYPE_4__ {TYPE_1__ vm; int /*<<< orphan*/  hdmi_dvi_mode; } ;
struct hdmi_core_vid_config {int data_enable_pol; int hblank; int vblank_osc; int vblank; TYPE_2__ v_fc_config; } ;
struct hdmi_config {TYPE_1__ vm; int /*<<< orphan*/  hdmi_dvi_mode; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_DOUBLECLK ; 
 int DISPLAY_FLAGS_INTERLACED ; 
 int /*<<< orphan*/  DSSDBG (char*) ; 

__attribute__((used)) static void hdmi_core_init(struct hdmi_core_vid_config *video_cfg,
			   const struct hdmi_config *cfg)
{
	DSSDBG("hdmi_core_init\n");

	video_cfg->v_fc_config.vm = cfg->vm;

	/* video core */
	video_cfg->data_enable_pol = 1; /* It is always 1*/
	video_cfg->hblank = cfg->vm.hfront_porch +
			    cfg->vm.hback_porch + cfg->vm.hsync_len;
	video_cfg->vblank_osc = 0;
	video_cfg->vblank = cfg->vm.vsync_len + cfg->vm.vfront_porch +
			    cfg->vm.vback_porch;
	video_cfg->v_fc_config.hdmi_dvi_mode = cfg->hdmi_dvi_mode;

	if (cfg->vm.flags & DISPLAY_FLAGS_INTERLACED) {
		/* set vblank_osc if vblank is fractional */
		if (video_cfg->vblank % 2 != 0)
			video_cfg->vblank_osc = 1;

		video_cfg->v_fc_config.vm.vactive /= 2;
		video_cfg->vblank /= 2;
		video_cfg->v_fc_config.vm.vfront_porch /= 2;
		video_cfg->v_fc_config.vm.vsync_len /= 2;
		video_cfg->v_fc_config.vm.vback_porch /= 2;
	}

	if (cfg->vm.flags & DISPLAY_FLAGS_DOUBLECLK) {
		video_cfg->v_fc_config.vm.hactive *= 2;
		video_cfg->hblank *= 2;
		video_cfg->v_fc_config.vm.hfront_porch *= 2;
		video_cfg->v_fc_config.vm.hsync_len *= 2;
		video_cfg->v_fc_config.vm.hback_porch *= 2;
	}
}