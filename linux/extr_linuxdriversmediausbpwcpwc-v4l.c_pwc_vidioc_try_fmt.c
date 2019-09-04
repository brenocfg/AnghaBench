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
struct TYPE_3__ {int pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_2__ fmt; } ;
struct pwc_device {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVICE_USE_CODEC23 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PWC_DEBUG_IOCTL (char*) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_PIX_FMT_PWC1 130 
#define  V4L2_PIX_FMT_PWC2 129 
#define  V4L2_PIX_FMT_YUV420 128 
 int pwc_get_size (struct pwc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** pwc_image_sizes ; 
 int /*<<< orphan*/  pwc_vidioc_fill_fmt (struct v4l2_format*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pwc_vidioc_try_fmt(struct pwc_device *pdev, struct v4l2_format *f)
{
	int size;

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		PWC_DEBUG_IOCTL("Bad video type must be V4L2_BUF_TYPE_VIDEO_CAPTURE\n");
		return -EINVAL;
	}

	switch (f->fmt.pix.pixelformat) {
		case V4L2_PIX_FMT_YUV420:
			break;
		case V4L2_PIX_FMT_PWC1:
			if (DEVICE_USE_CODEC23(pdev->type)) {
				PWC_DEBUG_IOCTL("codec1 is only supported for old pwc webcam\n");
				f->fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
			}
			break;
		case V4L2_PIX_FMT_PWC2:
			if (DEVICE_USE_CODEC1(pdev->type)) {
				PWC_DEBUG_IOCTL("codec23 is only supported for new pwc webcam\n");
				f->fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
			}
			break;
		default:
			PWC_DEBUG_IOCTL("Unsupported pixel format\n");
			f->fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
	}

	size = pwc_get_size(pdev, f->fmt.pix.width, f->fmt.pix.height);
	pwc_vidioc_fill_fmt(f,
			    pwc_image_sizes[size][0],
			    pwc_image_sizes[size][1],
			    f->fmt.pix.pixelformat);

	return 0;
}