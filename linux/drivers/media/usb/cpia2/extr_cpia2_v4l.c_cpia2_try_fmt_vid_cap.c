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
struct TYPE_3__ {scalar_t__ pixelformat; int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  sizeimage; scalar_t__ bytesperline; int /*<<< orphan*/  field; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct camera_data {int /*<<< orphan*/  frame_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_MJPEG ; 
#define  VIDEOSIZE_192_144 135 
#define  VIDEOSIZE_224_168 134 
#define  VIDEOSIZE_256_192 133 
#define  VIDEOSIZE_288_216 132 
#define  VIDEOSIZE_CIF 131 
#define  VIDEOSIZE_QCIF 130 
#define  VIDEOSIZE_QVGA 129 
#define  VIDEOSIZE_VGA 128 
 int cpia2_match_video_size (int,int) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int cpia2_try_fmt_vid_cap(struct file *file, void *fh,
					  struct v4l2_format *f)
{
	struct camera_data *cam = video_drvdata(file);

	if (f->fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG &&
	    f->fmt.pix.pixelformat != V4L2_PIX_FMT_JPEG)
	       return -EINVAL;

	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.bytesperline = 0;
	f->fmt.pix.sizeimage = cam->frame_size;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;

	switch (cpia2_match_video_size(f->fmt.pix.width, f->fmt.pix.height)) {
	case VIDEOSIZE_VGA:
		f->fmt.pix.width = 640;
		f->fmt.pix.height = 480;
		break;
	case VIDEOSIZE_CIF:
		f->fmt.pix.width = 352;
		f->fmt.pix.height = 288;
		break;
	case VIDEOSIZE_QVGA:
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
		break;
	case VIDEOSIZE_288_216:
		f->fmt.pix.width = 288;
		f->fmt.pix.height = 216;
		break;
	case VIDEOSIZE_256_192:
		f->fmt.pix.width = 256;
		f->fmt.pix.height = 192;
		break;
	case VIDEOSIZE_224_168:
		f->fmt.pix.width = 224;
		f->fmt.pix.height = 168;
		break;
	case VIDEOSIZE_192_144:
		f->fmt.pix.width = 192;
		f->fmt.pix.height = 144;
		break;
	case VIDEOSIZE_QCIF:
	default:
		f->fmt.pix.width = 176;
		f->fmt.pix.height = 144;
		break;
	}

	return 0;
}