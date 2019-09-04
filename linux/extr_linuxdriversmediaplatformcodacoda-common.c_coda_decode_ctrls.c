#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct coda_ctx {TYPE_4__* h264_level_ctrl; int /*<<< orphan*/  ctrls; TYPE_3__* dev; TYPE_1__* h264_profile_ctrl; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_2__* devtype; } ;
struct TYPE_6__ {scalar_t__ product; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CODA_7541 ; 
 scalar_t__ CODA_960 ; 
 scalar_t__ CODA_HX4 ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_READ_ONLY ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_2_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_1 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_2 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_1 ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 
 int /*<<< orphan*/  coda_ctrl_ops ; 
 void* v4l2_ctrl_new_std_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void coda_decode_ctrls(struct coda_ctx *ctx)
{
	u64 mask;
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
	    ctx->dev->devtype->product == CODA_7541) {
		max = V4L2_MPEG_VIDEO_H264_LEVEL_4_0;
		mask = ~((1 << V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_1) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_2) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_4_0));
	} else if (ctx->dev->devtype->product == CODA_960) {
		max = V4L2_MPEG_VIDEO_H264_LEVEL_4_1;
		mask = ~((1 << V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_1) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_2) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_4_0) |
			 (1 << V4L2_MPEG_VIDEO_H264_LEVEL_4_1));
	} else {
		return;
	}
	ctx->h264_level_ctrl = v4l2_ctrl_new_std_menu(&ctx->ctrls,
		&coda_ctrl_ops, V4L2_CID_MPEG_VIDEO_H264_LEVEL, max, mask,
		max);
	if (ctx->h264_level_ctrl)
		ctx->h264_level_ctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
}