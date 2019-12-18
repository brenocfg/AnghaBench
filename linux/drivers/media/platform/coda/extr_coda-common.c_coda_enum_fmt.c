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
typedef  scalar_t__ u32 ;
struct video_device {int dummy; } ;
struct v4l2_fmtdesc {scalar_t__ type; size_t index; scalar_t__ pixelformat; } ;
struct file {int dummy; } ;
struct coda_video_device {scalar_t__* src_formats; scalar_t__* dst_formats; } ;
struct coda_ctx {int /*<<< orphan*/  vdoa; } ;

/* Variables and functions */
 size_t CODA_MAX_FORMATS ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ const V4L2_PIX_FMT_YUYV ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 struct coda_video_device* to_coda_video_device (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int coda_enum_fmt(struct file *file, void *priv,
			 struct v4l2_fmtdesc *f)
{
	struct video_device *vdev = video_devdata(file);
	const struct coda_video_device *cvd = to_coda_video_device(vdev);
	struct coda_ctx *ctx = fh_to_ctx(priv);
	const u32 *formats;

	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		formats = cvd->src_formats;
	else if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		formats = cvd->dst_formats;
	else
		return -EINVAL;

	if (f->index >= CODA_MAX_FORMATS || formats[f->index] == 0)
		return -EINVAL;

	/* Skip YUYV if the vdoa is not available */
	if (!ctx->vdoa && f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    formats[f->index] == V4L2_PIX_FMT_YUYV)
		return -EINVAL;

	f->pixelformat = formats[f->index];

	return 0;
}