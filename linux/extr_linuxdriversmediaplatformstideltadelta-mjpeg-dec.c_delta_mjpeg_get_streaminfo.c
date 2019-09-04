#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct delta_streaminfo {int dpb; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  streamformat; } ;
struct delta_mjpeg_ctx {TYPE_1__* header; } ;
struct delta_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frame_height; int /*<<< orphan*/  frame_width; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MJPEG ; 
 struct delta_mjpeg_ctx* to_ctx (struct delta_ctx*) ; 

__attribute__((used)) static int delta_mjpeg_get_streaminfo(struct delta_ctx *pctx,
				      struct delta_streaminfo *streaminfo)
{
	struct delta_mjpeg_ctx *ctx = to_ctx(pctx);

	if (!ctx->header)
		goto nodata;

	streaminfo->streamformat = V4L2_PIX_FMT_MJPEG;
	streaminfo->width = ctx->header->frame_width;
	streaminfo->height = ctx->header->frame_height;

	/* progressive stream */
	streaminfo->field = V4L2_FIELD_NONE;

	streaminfo->dpb = 1;

	return 0;

nodata:
	return -ENODATA;
}