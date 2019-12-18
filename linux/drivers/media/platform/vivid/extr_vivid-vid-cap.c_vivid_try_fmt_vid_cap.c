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
struct vivid_fmt {unsigned int buffers; int* bit_depth; int* vdownsampling; unsigned int planes; scalar_t__ color_enc; scalar_t__* data_offset; } ;
struct v4l2_rect {unsigned int width; unsigned int height; unsigned int member_2; unsigned int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct vivid_dev {int* std_cap; size_t input; struct v4l2_rect src_rect; scalar_t__ has_crop_cap; scalar_t__ has_scaler_cap; int /*<<< orphan*/  has_compose_cap; } ;
struct v4l2_plane_pix_format {unsigned int bytesperline; scalar_t__ sizeimage; int /*<<< orphan*/  reserved; } ;
struct v4l2_pix_format_mplane {unsigned int width; unsigned int height; unsigned int num_planes; int /*<<< orphan*/  reserved; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  hsv_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; struct v4l2_plane_pix_format* plane_fmt; } ;
struct v4l2_frmsize_discrete {unsigned int width; unsigned int height; } ;
struct TYPE_2__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_WIDTH ; 
 unsigned int MAX_ZOOM ; 
 scalar_t__ TGP_COLOR_ENC_HSV ; 
 scalar_t__ V4L2_FIELD_HAS_T_OR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VIVID_WEBCAM_SIZES ; 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct v4l2_frmsize_discrete* v4l2_find_nearest_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  v4l2_rect_set_max_size (struct v4l2_rect*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  v4l2_rect_set_min_size (struct v4l2_rect*,struct v4l2_rect*) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_colorspace_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_field_cap (struct vivid_dev*,int /*<<< orphan*/ ) ; 
 struct vivid_fmt* vivid_get_format (struct vivid_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vivid_hsv_enc_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_webcam (struct vivid_dev*) ; 
 struct v4l2_rect vivid_max_rect ; 
 struct v4l2_rect vivid_min_rect ; 
 int /*<<< orphan*/  vivid_quantization_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_xfer_func_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_ycbcr_enc_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  webcam_sizes ; 
 int /*<<< orphan*/  width ; 

int vivid_try_fmt_vid_cap(struct file *file, void *priv,
			struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *mp = &f->fmt.pix_mp;
	struct v4l2_plane_pix_format *pfmt = mp->plane_fmt;
	struct vivid_dev *dev = video_drvdata(file);
	const struct vivid_fmt *fmt;
	unsigned bytesperline, max_bpl;
	unsigned factor = 1;
	unsigned w, h;
	unsigned p;

	fmt = vivid_get_format(dev, mp->pixelformat);
	if (!fmt) {
		dprintk(dev, 1, "Fourcc format (0x%08x) unknown.\n",
			mp->pixelformat);
		mp->pixelformat = V4L2_PIX_FMT_YUYV;
		fmt = vivid_get_format(dev, mp->pixelformat);
	}

	mp->field = vivid_field_cap(dev, mp->field);
	if (vivid_is_webcam(dev)) {
		const struct v4l2_frmsize_discrete *sz =
			v4l2_find_nearest_size(webcam_sizes,
					       VIVID_WEBCAM_SIZES, width,
					       height, mp->width, mp->height);

		w = sz->width;
		h = sz->height;
	} else if (vivid_is_sdtv_cap(dev)) {
		w = 720;
		h = (dev->std_cap[dev->input] & V4L2_STD_525_60) ? 480 : 576;
	} else {
		w = dev->src_rect.width;
		h = dev->src_rect.height;
	}
	if (V4L2_FIELD_HAS_T_OR_B(mp->field))
		factor = 2;
	if (vivid_is_webcam(dev) ||
	    (!dev->has_scaler_cap && !dev->has_crop_cap && !dev->has_compose_cap)) {
		mp->width = w;
		mp->height = h / factor;
	} else {
		struct v4l2_rect r = { 0, 0, mp->width, mp->height * factor };

		v4l2_rect_set_min_size(&r, &vivid_min_rect);
		v4l2_rect_set_max_size(&r, &vivid_max_rect);
		if (dev->has_scaler_cap && !dev->has_compose_cap) {
			struct v4l2_rect max_r = { 0, 0, MAX_ZOOM * w, MAX_ZOOM * h };

			v4l2_rect_set_max_size(&r, &max_r);
		} else if (!dev->has_scaler_cap && dev->has_crop_cap && !dev->has_compose_cap) {
			v4l2_rect_set_max_size(&r, &dev->src_rect);
		} else if (!dev->has_scaler_cap && !dev->has_crop_cap) {
			v4l2_rect_set_min_size(&r, &dev->src_rect);
		}
		mp->width = r.width;
		mp->height = r.height / factor;
	}

	/* This driver supports custom bytesperline values */

	mp->num_planes = fmt->buffers;
	for (p = 0; p < fmt->buffers; p++) {
		/* Calculate the minimum supported bytesperline value */
		bytesperline = (mp->width * fmt->bit_depth[p]) >> 3;
		/* Calculate the maximum supported bytesperline value */
		max_bpl = (MAX_ZOOM * MAX_WIDTH * fmt->bit_depth[p]) >> 3;

		if (pfmt[p].bytesperline > max_bpl)
			pfmt[p].bytesperline = max_bpl;
		if (pfmt[p].bytesperline < bytesperline)
			pfmt[p].bytesperline = bytesperline;

		pfmt[p].sizeimage = (pfmt[p].bytesperline * mp->height) /
				fmt->vdownsampling[p] + fmt->data_offset[p];

		memset(pfmt[p].reserved, 0, sizeof(pfmt[p].reserved));
	}
	for (p = fmt->buffers; p < fmt->planes; p++)
		pfmt[0].sizeimage += (pfmt[0].bytesperline * mp->height *
			(fmt->bit_depth[p] / fmt->vdownsampling[p])) /
			(fmt->bit_depth[0] / fmt->vdownsampling[0]);

	mp->colorspace = vivid_colorspace_cap(dev);
	if (fmt->color_enc == TGP_COLOR_ENC_HSV)
		mp->hsv_enc = vivid_hsv_enc_cap(dev);
	else
		mp->ycbcr_enc = vivid_ycbcr_enc_cap(dev);
	mp->xfer_func = vivid_xfer_func_cap(dev);
	mp->quantization = vivid_quantization_cap(dev);
	memset(mp->reserved, 0, sizeof(mp->reserved));
	return 0;
}