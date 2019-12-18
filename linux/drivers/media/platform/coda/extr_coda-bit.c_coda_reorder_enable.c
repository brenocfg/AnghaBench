#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct coda_dev {int /*<<< orphan*/  v4l2_dev; TYPE_3__* devtype; } ;
struct TYPE_5__ {int /*<<< orphan*/  h264_profile_idc; } ;
struct coda_ctx {TYPE_2__ params; TYPE_1__* codec; struct coda_dev* dev; } ;
struct TYPE_6__ {scalar_t__ product; } ;
struct TYPE_4__ {scalar_t__ src_fourcc; } ;

/* Variables and functions */
 scalar_t__ CODA_7541 ; 
 scalar_t__ CODA_960 ; 
 scalar_t__ CODA_HX4 ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int coda_h264_profile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool coda_reorder_enable(struct coda_ctx *ctx)
{
	struct coda_dev *dev = ctx->dev;
	int profile;

	if (dev->devtype->product != CODA_HX4 &&
	    dev->devtype->product != CODA_7541 &&
	    dev->devtype->product != CODA_960)
		return false;

	if (ctx->codec->src_fourcc == V4L2_PIX_FMT_JPEG)
		return false;

	if (ctx->codec->src_fourcc != V4L2_PIX_FMT_H264)
		return true;

	profile = coda_h264_profile(ctx->params.h264_profile_idc);
	if (profile < 0)
		v4l2_warn(&dev->v4l2_dev, "Unknown H264 Profile: %u\n",
			  ctx->params.h264_profile_idc);

	/* Baseline profile does not support reordering */
	return profile > V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE;
}