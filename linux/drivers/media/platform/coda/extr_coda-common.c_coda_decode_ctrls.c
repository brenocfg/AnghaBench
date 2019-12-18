#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct coda_ctx {TYPE_8__* mpeg4_level_ctrl; int /*<<< orphan*/  ctrls; TYPE_7__* mpeg4_profile_ctrl; TYPE_6__* mpeg2_level_ctrl; TYPE_5__* mpeg2_profile_ctrl; TYPE_4__* h264_level_ctrl; TYPE_3__* dev; TYPE_1__* h264_profile_ctrl; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {TYPE_2__* devtype; } ;
struct TYPE_10__ {scalar_t__ product; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CODA_7541 ; 
 scalar_t__ CODA_960 ; 
 scalar_t__ CODA_HX4 ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_READ_ONLY ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_1 ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 
 int V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH ; 
 int V4L2_MPEG_VIDEO_MPEG2_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY ; 
 int /*<<< orphan*/  coda_ctrl_ops ; 
 void* v4l2_ctrl_new_std_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void coda_decode_ctrls(struct coda_ctx *ctx)
{
	u8 max;

	ctx->h264_profile_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_H264_PROFILE,
		V4L2_MPEG_VIDEO_H264_PROFILE_HIGH,
		~((1 << V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_HIGH)),
		V4L2_MPEG_VIDEO_H264_PROFILE_HIGH);
	if (ctx->h264_profile_ctrl)
		ctx->h264_profile_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	if (ctx->dev->devtype->product == CODA_HX4 ||
	    ctx->dev->devtype->product == CODA_7541)
		max = V4L2_MPEG_VIDEO_H264_LEVEL_4_0;
	else if (ctx->dev->devtype->product == CODA_960)
		max = V4L2_MPEG_VIDEO_H264_LEVEL_4_1;
	else
		return;
	ctx->h264_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_H264_LEVEL, max, 0, max);
	if (ctx->h264_level_ctrl)
		ctx->h264_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg2_profile_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG2_PROFILE,
		V4L2_MPEG_VIDEO_MPEG2_PROFILE_HIGH, 0,
		V4L2_MPEG_VIDEO_MPEG2_PROFILE_HIGH);
	if (ctx->mpeg2_profile_ctrl)
		ctx->mpeg2_profile_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg2_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG2_LEVEL,
		V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH, 0,
		V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH);
	if (ctx->mpeg2_level_ctrl)
		ctx->mpeg2_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg4_profile_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE,
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY, 0,
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY);
	if (ctx->mpeg4_profile_ctrl)
		ctx->mpeg4_profile_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;

	ctx->mpeg4_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
		V4L2_MPEG_VIDEO_MPEG4_LEVEL_5, 0,
		V4L2_MPEG_VIDEO_MPEG4_LEVEL_5);
	if (ctx->mpeg4_level_ctrl)
		ctx->mpeg4_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
}