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
struct delta_streaminfo {int flags; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelaspect; int /*<<< orphan*/  crop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct delta_frameinfo {int /*<<< orphan*/  field; int /*<<< orphan*/  pixelaspect; int /*<<< orphan*/  flags; int /*<<< orphan*/  crop; int /*<<< orphan*/  pixelformat; void* aligned_height; void* aligned_width; int /*<<< orphan*/  size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct delta_ctx {struct delta_streaminfo streaminfo; } ;

/* Variables and functions */
 void* ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELTA_FRAMEINFO_FLAG_CROP ; 
 int /*<<< orphan*/  DELTA_FRAMEINFO_FLAG_PIXELASPECT ; 
 int /*<<< orphan*/  DELTA_HEIGHT_ALIGNMENT ; 
 int DELTA_STREAMINFO_FLAG_CROP ; 
 int DELTA_STREAMINFO_FLAG_PIXELASPECT ; 
 int /*<<< orphan*/  DELTA_WIDTH_ALIGNMENT ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  frame_size (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct delta_frameinfo*,int /*<<< orphan*/ ,int) ; 

int delta_get_frameinfo_default(struct delta_ctx *ctx,
				struct delta_frameinfo *frameinfo)
{
	struct delta_streaminfo *streaminfo = &ctx->streaminfo;

	memset(frameinfo, 0, sizeof(*frameinfo));
	frameinfo->pixelformat = V4L2_PIX_FMT_NV12;
	frameinfo->width = streaminfo->width;
	frameinfo->height = streaminfo->height;
	frameinfo->aligned_width = ALIGN(streaminfo->width,
					 DELTA_WIDTH_ALIGNMENT);
	frameinfo->aligned_height = ALIGN(streaminfo->height,
					  DELTA_HEIGHT_ALIGNMENT);
	frameinfo->size = frame_size(frameinfo->aligned_width,
				     frameinfo->aligned_height,
				     frameinfo->pixelformat);
	if (streaminfo->flags & DELTA_STREAMINFO_FLAG_CROP) {
		frameinfo->flags |= DELTA_FRAMEINFO_FLAG_CROP;
		frameinfo->crop = streaminfo->crop;
	}
	if (streaminfo->flags & DELTA_STREAMINFO_FLAG_PIXELASPECT) {
		frameinfo->flags |= DELTA_FRAMEINFO_FLAG_PIXELASPECT;
		frameinfo->pixelaspect = streaminfo->pixelaspect;
	}
	frameinfo->field = streaminfo->field;

	return 0;
}