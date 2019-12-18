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
struct TYPE_3__ {int width; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; scalar_t__ bytesperline; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct hdpvr_video_info {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  valid; } ;
struct hdpvr_fh {scalar_t__ legacy_mode; } ;
struct hdpvr_device {int width; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  height; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_MPEG ; 
 int get_video_info (struct hdpvr_device*,struct hdpvr_video_info*) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fmt_vid_cap(struct file *file, void *_fh,
				struct v4l2_format *f)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;
	int ret;

	/*
	 * The original driver would always returns the current detected
	 * resolution as the format (and EFAULT if it couldn't be detected).
	 * With the introduction of VIDIOC_QUERY_DV_TIMINGS there is now a
	 * better way of doing this, but to stay compatible with existing
	 * applications we assume legacy mode every time an application opens
	 * the device. Only if one of the new DV_TIMINGS ioctls is called
	 * will the filehandle go into 'normal' mode where g_fmt returns the
	 * last set format.
	 */
	if (fh->legacy_mode) {
		struct hdpvr_video_info vid_info;

		ret = get_video_info(dev, &vid_info);
		if (ret < 0)
			return ret;
		if (!vid_info.valid)
			return -EFAULT;
		f->fmt.pix.width = vid_info.width;
		f->fmt.pix.height = vid_info.height;
	} else {
		f->fmt.pix.width = dev->width;
		f->fmt.pix.height = dev->height;
	}
	f->fmt.pix.pixelformat	= V4L2_PIX_FMT_MPEG;
	f->fmt.pix.sizeimage	= dev->bulk_in_size;
	f->fmt.pix.bytesperline	= 0;
	if (f->fmt.pix.width == 720) {
		/* SDTV formats */
		f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
		f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else {
		/* HDTV formats */
		f->fmt.pix.colorspace = V4L2_COLORSPACE_REC709;
		f->fmt.pix.field = V4L2_FIELD_NONE;
	}
	return 0;
}