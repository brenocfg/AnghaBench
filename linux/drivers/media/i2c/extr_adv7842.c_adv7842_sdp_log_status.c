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

/* Variables and functions */
 int io_read (struct v4l2_subdev*,int) ; 
 scalar_t__ no_power (struct v4l2_subdev*) ; 
 int sdp_io_read (struct v4l2_subdev*,int) ; 
 int sdp_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int adv7842_sdp_log_status(struct v4l2_subdev *sd)
{
	/* SDP (Standard definition processor) block */
	u8 sdp_signal_detected = sdp_read(sd, 0x5A) & 0x01;

	v4l2_info(sd, "Chip powered %s\n", no_power(sd) ? "off" : "on");
	v4l2_info(sd, "Prim-mode = 0x%x, video std = 0x%x\n",
		  io_read(sd, 0x01) & 0x0f, io_read(sd, 0x00) & 0x3f);

	v4l2_info(sd, "SDP: free run: %s\n",
		(sdp_read(sd, 0x56) & 0x01) ? "on" : "off");
	v4l2_info(sd, "SDP: %s\n", sdp_signal_detected ?
		"valid SD/PR signal detected" : "invalid/no signal");
	if (sdp_signal_detected) {
		static const char * const sdp_std_txt[] = {
			"NTSC-M/J",
			"1?",
			"NTSC-443",
			"60HzSECAM",
			"PAL-M",
			"5?",
			"PAL-60",
			"7?", "8?", "9?", "a?", "b?",
			"PAL-CombN",
			"d?",
			"PAL-BGHID",
			"SECAM"
		};
		v4l2_info(sd, "SDP: standard %s\n",
			sdp_std_txt[sdp_read(sd, 0x52) & 0x0f]);
		v4l2_info(sd, "SDP: %s\n",
			(sdp_read(sd, 0x59) & 0x08) ? "50Hz" : "60Hz");
		v4l2_info(sd, "SDP: %s\n",
			(sdp_read(sd, 0x57) & 0x08) ? "Interlaced" : "Progressive");
		v4l2_info(sd, "SDP: deinterlacer %s\n",
			(sdp_read(sd, 0x12) & 0x08) ? "enabled" : "disabled");
		v4l2_info(sd, "SDP: csc %s mode\n",
			(sdp_io_read(sd, 0xe0) & 0x40) ? "auto" : "manual");
	}
	return 0;
}