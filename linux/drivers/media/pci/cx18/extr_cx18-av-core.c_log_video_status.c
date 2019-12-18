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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {int vid_input; int audclk_freq; struct v4l2_subdev sd; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 int CX18_AV_COMPOSITE1 ; 
 int CX18_AV_COMPOSITE8 ; 
 int /*<<< orphan*/  CX18_INFO_DEV (struct v4l2_subdev*,char*,...) ; 
 int cx18_av_read (struct cx18*,int) ; 

__attribute__((used)) static void log_video_status(struct cx18 *cx)
{
	static const char *const fmt_strs[] = {
		"0x0",
		"NTSC-M", "NTSC-J", "NTSC-4.43",
		"PAL-BDGHI", "PAL-M", "PAL-N", "PAL-Nc", "PAL-60",
		"0x9", "0xA", "0xB",
		"SECAM",
		"0xD", "0xE", "0xF"
	};

	struct cx18_av_state *state = &cx->av_state;
	struct v4l2_subdev *sd = &state->sd;
	u8 vidfmt_sel = cx18_av_read(cx, 0x400) & 0xf;
	u8 gen_stat1 = cx18_av_read(cx, 0x40d);
	u8 gen_stat2 = cx18_av_read(cx, 0x40e);
	int vid_input = state->vid_input;

	CX18_INFO_DEV(sd, "Video signal:              %spresent\n",
		      (gen_stat2 & 0x20) ? "" : "not ");
	CX18_INFO_DEV(sd, "Detected format:           %s\n",
		      fmt_strs[gen_stat1 & 0xf]);

	CX18_INFO_DEV(sd, "Specified standard:        %s\n",
		      vidfmt_sel ? fmt_strs[vidfmt_sel]
				 : "automatic detection");

	if (vid_input >= CX18_AV_COMPOSITE1 &&
	    vid_input <= CX18_AV_COMPOSITE8) {
		CX18_INFO_DEV(sd, "Specified video input:     Composite %d\n",
			      vid_input - CX18_AV_COMPOSITE1 + 1);
	} else {
		CX18_INFO_DEV(sd, "Specified video input:     S-Video (Luma In%d, Chroma In%d)\n",
			      (vid_input & 0xf0) >> 4,
			      (vid_input & 0xf00) >> 8);
	}

	CX18_INFO_DEV(sd, "Specified audioclock freq: %d Hz\n",
		      state->audclk_freq);
}