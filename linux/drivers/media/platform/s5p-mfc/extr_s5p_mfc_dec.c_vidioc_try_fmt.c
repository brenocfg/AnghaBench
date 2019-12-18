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
struct v4l2_format {scalar_t__ type; } ;
struct s5p_mfc_fmt {scalar_t__ codec_mode; int versions; } ;
struct s5p_mfc_dev {TYPE_1__* variant; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int version_bit; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MFC_FMT_DEC ; 
 int /*<<< orphan*/  MFC_FMT_RAW ; 
 scalar_t__ S5P_FIMV_CODEC_NONE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct s5p_mfc_fmt* find_format (struct v4l2_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 struct s5p_mfc_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_fmt *fmt;

	mfc_debug(2, "Type is %d\n", f->type);
	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		fmt = find_format(f, MFC_FMT_DEC);
		if (!fmt) {
			mfc_err("Unsupported format for source.\n");
			return -EINVAL;
		}
		if (fmt->codec_mode == S5P_FIMV_CODEC_NONE) {
			mfc_err("Unknown codec\n");
			return -EINVAL;
		}
		if ((dev->variant->version_bit & fmt->versions) == 0) {
			mfc_err("Unsupported format by this MFC version.\n");
			return -EINVAL;
		}
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		fmt = find_format(f, MFC_FMT_RAW);
		if (!fmt) {
			mfc_err("Unsupported format for destination.\n");
			return -EINVAL;
		}
		if ((dev->variant->version_bit & fmt->versions) == 0) {
			mfc_err("Unsupported format by this MFC version.\n");
			return -EINVAL;
		}
	}

	return 0;
}