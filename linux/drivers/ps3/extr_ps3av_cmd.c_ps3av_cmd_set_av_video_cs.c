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
struct ps3av_pkt_av_video_cs {int avport; int aspect; int dither; int /*<<< orphan*/  super_white; int /*<<< orphan*/  bitlen_out; void* av_cs_in; void* av_cs_out; int /*<<< orphan*/  av_vid; int /*<<< orphan*/  send_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3AV_CID_AV_VIDEO_CS ; 
 int PS3AV_CMD_AV_DITHER_8BIT ; 
 int PS3AV_CMD_AV_DITHER_OFF ; 
 int PS3AV_CMD_AV_DITHER_ON ; 
 int /*<<< orphan*/  PS3AV_CMD_AV_SUPER_WHITE_OFF ; 
 int /*<<< orphan*/  PS3AV_CMD_AV_SUPER_WHITE_ON ; 
 int PS3AV_CMD_VIDEO_CS_RGB_8 ; 
 int PS3AV_CMD_VIDEO_CS_YUV444_8 ; 
 int PS3AV_CMD_VIDEO_VID_720P_60HZ ; 
 int PS3AV_MODE_DITHER ; 
 int PS3AV_MODE_WHITE ; 
 int /*<<< orphan*/  memset (struct ps3av_pkt_av_video_cs*,int /*<<< orphan*/ ,int) ; 
 void* ps3av_cs_video2av (int) ; 
 int /*<<< orphan*/  ps3av_cs_video2av_bitlen (int) ; 
 scalar_t__ ps3av_hdmi_range () ; 
 int /*<<< orphan*/  ps3av_set_hdr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3av_vid_video2av (int) ; 

u32 ps3av_cmd_set_av_video_cs(void *p, u32 avport, int video_vid, int cs_out,
			      int aspect, u32 id)
{
	struct ps3av_pkt_av_video_cs *av_video_cs;

	av_video_cs = (struct ps3av_pkt_av_video_cs *)p;
	if (video_vid == -1)
		video_vid = PS3AV_CMD_VIDEO_VID_720P_60HZ;
	if (cs_out == -1)
		cs_out = PS3AV_CMD_VIDEO_CS_YUV444_8;
	if (aspect == -1)
		aspect = 0;

	memset(av_video_cs, 0, sizeof(*av_video_cs));
	ps3av_set_hdr(PS3AV_CID_AV_VIDEO_CS, sizeof(*av_video_cs),
		      &av_video_cs->send_hdr);
	av_video_cs->avport = avport;
	/* should be same as video_mode.resolution */
	av_video_cs->av_vid = ps3av_vid_video2av(video_vid);
	av_video_cs->av_cs_out = ps3av_cs_video2av(cs_out);
	/* should be same as video_mode.video_cs_out */
	av_video_cs->av_cs_in = ps3av_cs_video2av(PS3AV_CMD_VIDEO_CS_RGB_8);
	av_video_cs->bitlen_out = ps3av_cs_video2av_bitlen(cs_out);
	if ((id & PS3AV_MODE_WHITE) && ps3av_hdmi_range())
		av_video_cs->super_white = PS3AV_CMD_AV_SUPER_WHITE_ON;
	else /* default off */
		av_video_cs->super_white = PS3AV_CMD_AV_SUPER_WHITE_OFF;
	av_video_cs->aspect = aspect;
	if (id & PS3AV_MODE_DITHER) {
		av_video_cs->dither = PS3AV_CMD_AV_DITHER_ON
		    | PS3AV_CMD_AV_DITHER_8BIT;
	} else {
		/* default off */
		av_video_cs->dither = PS3AV_CMD_AV_DITHER_OFF;
	}

	return sizeof(*av_video_cs);
}