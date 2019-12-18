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
struct go7007 {int format; int pali; int gop_size; int ipb; int closed_gop; int repeat_seqhead; int gop_header_enable; int dvd_mode; int bitrate; void* aspect_ratio; int /*<<< orphan*/  mpeg_video_aspect_ratio; int /*<<< orphan*/  mpeg_video_rep_seqheader; int /*<<< orphan*/  mpeg_video_bitrate; int /*<<< orphan*/  mpeg_video_b_frames; int /*<<< orphan*/  mpeg_video_gop_closure; int /*<<< orphan*/  mpeg_video_gop_size; scalar_t__ seq_header_enable; } ;

/* Variables and functions */
 void* GO7007_RATIO_16_9 ; 
 void* GO7007_RATIO_1_1 ; 
 void* GO7007_RATIO_4_3 ; 
#define  V4L2_MPEG_VIDEO_ASPECT_16x9 133 
#define  V4L2_MPEG_VIDEO_ASPECT_1x1 132 
#define  V4L2_MPEG_VIDEO_ASPECT_4x3 131 
 int V4L2_PIX_FMT_MJPEG ; 
#define  V4L2_PIX_FMT_MPEG1 130 
#define  V4L2_PIX_FMT_MPEG2 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_formatting(struct go7007 *go)
{
	if (go->format == V4L2_PIX_FMT_MJPEG) {
		go->pali = 0;
		go->aspect_ratio = GO7007_RATIO_1_1;
		go->gop_size = 0;
		go->ipb = 0;
		go->closed_gop = 0;
		go->repeat_seqhead = 0;
		go->seq_header_enable = 0;
		go->gop_header_enable = 0;
		go->dvd_mode = 0;
		return;
	}

	switch (go->format) {
	case V4L2_PIX_FMT_MPEG1:
		go->pali = 0;
		break;
	default:
	case V4L2_PIX_FMT_MPEG2:
		go->pali = 0x48;
		break;
	case V4L2_PIX_FMT_MPEG4:
		/* For future reference: this is the list of MPEG4
		 * profiles that are available, although they are
		 * untested:
		 *
		 * Profile		pali
		 * --------------	----
		 * PROFILE_S_L0		0x08
		 * PROFILE_S_L1		0x01
		 * PROFILE_S_L2		0x02
		 * PROFILE_S_L3		0x03
		 * PROFILE_ARTS_L1	0x91
		 * PROFILE_ARTS_L2	0x92
		 * PROFILE_ARTS_L3	0x93
		 * PROFILE_ARTS_L4	0x94
		 * PROFILE_AS_L0	0xf0
		 * PROFILE_AS_L1	0xf1
		 * PROFILE_AS_L2	0xf2
		 * PROFILE_AS_L3	0xf3
		 * PROFILE_AS_L4	0xf4
		 * PROFILE_AS_L5	0xf5
		 */
		go->pali = 0xf5;
		break;
	}
	go->gop_size = v4l2_ctrl_g_ctrl(go->mpeg_video_gop_size);
	go->closed_gop = v4l2_ctrl_g_ctrl(go->mpeg_video_gop_closure);
	go->ipb = v4l2_ctrl_g_ctrl(go->mpeg_video_b_frames) != 0;
	go->bitrate = v4l2_ctrl_g_ctrl(go->mpeg_video_bitrate);
	go->repeat_seqhead = v4l2_ctrl_g_ctrl(go->mpeg_video_rep_seqheader);
	go->gop_header_enable = 1;
	go->dvd_mode = 0;
	if (go->format == V4L2_PIX_FMT_MPEG2)
		go->dvd_mode =
			go->bitrate == 9800000 &&
			go->gop_size == 15 &&
			go->ipb == 0 &&
			go->repeat_seqhead == 1 &&
			go->closed_gop;

	switch (v4l2_ctrl_g_ctrl(go->mpeg_video_aspect_ratio)) {
	default:
	case V4L2_MPEG_VIDEO_ASPECT_1x1:
		go->aspect_ratio = GO7007_RATIO_1_1;
		break;
	case V4L2_MPEG_VIDEO_ASPECT_4x3:
		go->aspect_ratio = GO7007_RATIO_4_3;
		break;
	case V4L2_MPEG_VIDEO_ASPECT_16x9:
		go->aspect_ratio = GO7007_RATIO_16_9;
		break;
	}
}