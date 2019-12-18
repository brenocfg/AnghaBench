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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_ctrl {int dummy; } ;
struct coda_ctx {TYPE_2__* dev; struct v4l2_ctrl* mpeg4_level_ctrl; struct v4l2_ctrl* mpeg4_profile_ctrl; struct v4l2_ctrl* mpeg2_level_ctrl; struct v4l2_ctrl* mpeg2_profile_ctrl; struct v4l2_ctrl* h264_level_ctrl; struct v4l2_ctrl* h264_profile_ctrl; TYPE_1__* codec; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_3__ {int src_fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE ; 
#define  V4L2_PIX_FMT_H264 130 
#define  V4L2_PIX_FMT_MPEG2 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 int /*<<< orphan*/  coda_dbg (int,struct coda_ctx*,char*,char const*,char const* const) ; 
 int coda_h264_level (int /*<<< orphan*/ ) ; 
 int coda_h264_profile (int /*<<< orphan*/ ) ; 
 int coda_mpeg2_level (int /*<<< orphan*/ ) ; 
 int coda_mpeg2_profile (int /*<<< orphan*/ ) ; 
 int coda_mpeg4_level (int /*<<< orphan*/ ) ; 
 int coda_mpeg4_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_update_menu_ctrl (struct v4l2_ctrl*,int) ; 
 char** v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

void coda_update_profile_level_ctrls(struct coda_ctx *ctx, u8 profile_idc,
				     u8 level_idc)
{
	const char * const *profile_names;
	const char * const *level_names;
	struct v4l2_ctrl *profile_ctrl;
	struct v4l2_ctrl *level_ctrl;
	const char *codec_name;
	u32 profile_cid;
	u32 level_cid;
	int profile;
	int level;

	switch (ctx->codec->src_fourcc) {
	case V4L2_PIX_FMT_H264:
		codec_name = "H264";
		profile_cid = V4L2_CID_MPEG_VIDEO_H264_PROFILE;
		level_cid = V4L2_CID_MPEG_VIDEO_H264_LEVEL;
		profile_ctrl = ctx->h264_profile_ctrl;
		level_ctrl = ctx->h264_level_ctrl;
		profile = coda_h264_profile(profile_idc);
		level = coda_h264_level(level_idc);
		break;
	case V4L2_PIX_FMT_MPEG2:
		codec_name = "MPEG-2";
		profile_cid = V4L2_CID_MPEG_VIDEO_MPEG2_PROFILE;
		level_cid = V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL;
		profile_ctrl = ctx->mpeg2_profile_ctrl;
		level_ctrl = ctx->mpeg2_level_ctrl;
		profile = coda_mpeg2_profile(profile_idc);
		level = coda_mpeg2_level(level_idc);
		break;
	case V4L2_PIX_FMT_MPEG4:
		codec_name = "MPEG-4";
		profile_cid = V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE;
		level_cid = V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL;
		profile_ctrl = ctx->mpeg4_profile_ctrl;
		level_ctrl = ctx->mpeg4_level_ctrl;
		profile = coda_mpeg4_profile(profile_idc);
		level = coda_mpeg4_level(level_idc);
		break;
	default:
		return;
	}

	profile_names = v4l2_ctrl_get_menu(profile_cid);
	level_names = v4l2_ctrl_get_menu(level_cid);

	if (profile < 0) {
		v4l2_warn(&ctx->dev->v4l2_dev, "Invalid %s profile: %u\n",
			  codec_name, profile_idc);
	} else {
		coda_dbg(1, ctx, "Parsed %s profile: %s\n", codec_name,
			 profile_names[profile]);
		coda_update_menu_ctrl(profile_ctrl, profile);
	}

	if (level < 0) {
		v4l2_warn(&ctx->dev->v4l2_dev, "Invalid %s level: %u\n",
			  codec_name, level_idc);
	} else {
		coda_dbg(1, ctx, "Parsed %s level: %s\n", codec_name,
			 level_names[level]);
		coda_update_menu_ctrl(level_ctrl, level);
	}
}