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
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* plane_fmt; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct s5p_mfc_fmt {int versions; } ;
struct s5p_mfc_dev {TYPE_3__* variant; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int version_bit; } ;
struct TYPE_5__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MFC_FMT_ENC ; 
 int /*<<< orphan*/  MFC_FMT_RAW ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct s5p_mfc_fmt* find_format (struct v4l2_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 struct s5p_mfc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_fmt *fmt;
	struct v4l2_pix_format_mplane *pix_fmt_mp = &f->fmt.pix_mp;

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		fmt = find_format(f, MFC_FMT_ENC);
		if (!fmt) {
			mfc_err("failed to try output format\n");
			return -EINVAL;
		}
		if ((dev->variant->version_bit & fmt->versions) == 0) {
			mfc_err("Unsupported format by this MFC version.\n");
			return -EINVAL;
		}

		pix_fmt_mp->plane_fmt[0].bytesperline =
			pix_fmt_mp->plane_fmt[0].sizeimage;
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		fmt = find_format(f, MFC_FMT_RAW);
		if (!fmt) {
			mfc_err("failed to try output format\n");
			return -EINVAL;
		}
		if ((dev->variant->version_bit & fmt->versions) == 0) {
			mfc_err("Unsupported format by this MFC version.\n");
			return -EINVAL;
		}

		v4l_bound_align_image(&pix_fmt_mp->width, 8, 1920, 1,
			&pix_fmt_mp->height, 4, 1080, 1, 0);
	} else {
		mfc_err("invalid buf type\n");
		return -EINVAL;
	}
	return 0;
}