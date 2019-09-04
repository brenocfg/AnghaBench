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
struct TYPE_4__ {int /*<<< orphan*/  h264_profile_idc; } ;
struct coda_ctx {TYPE_1__* dev; int /*<<< orphan*/  h264_profile_ctrl; TYPE_2__ params; } ;
struct TYPE_3__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  coda_debug ; 
 int coda_h264_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_update_menu_ctrl (int /*<<< orphan*/ ,int) ; 
 char** v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const* const) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coda_update_h264_profile_ctrl(struct coda_ctx *ctx)
{
	const char * const *profile_names;
	int profile;

	profile = coda_h264_profile(ctx->params.h264_profile_idc);
	if (profile < 0) {
		v4l2_warn(&ctx->dev->v4l2_dev, "Invalid H264 Profile: %u\n",
			  ctx->params.h264_profile_idc);
		return;
	}

	coda_update_menu_ctrl(ctx->h264_profile_ctrl, profile);

	profile_names = v4l2_ctrl_get_menu(V4L2_CID_MPEG_VIDEO_H264_PROFILE);

	v4l2_dbg(1, coda_debug, &ctx->dev->v4l2_dev, "Parsed H264 Profile: %s\n",
		 profile_names[profile]);
}