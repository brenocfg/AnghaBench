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
struct vivid_fmt {unsigned int buffers; int* bit_depth; int* vdownsampling; unsigned int planes; scalar_t__* data_offset; } ;
struct v4l2_rect {unsigned int width; unsigned int height; unsigned int member_2; unsigned int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct v4l2_bt_timings {int flags; int width; int height; } ;
struct TYPE_3__ {struct v4l2_bt_timings bt; } ;
struct vivid_dev {int std_out; scalar_t__ dvi_d_out; struct v4l2_rect sink_rect; scalar_t__ has_compose_out; scalar_t__ has_scaler_out; int /*<<< orphan*/  has_crop_out; TYPE_1__ dv_timings_out; } ;
struct v4l2_plane_pix_format {unsigned int bytesperline; scalar_t__ sizeimage; int /*<<< orphan*/  reserved; } ;
struct v4l2_pix_format_mplane {unsigned int width; unsigned int height; unsigned int num_planes; scalar_t__ colorspace; int /*<<< orphan*/  reserved; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; struct v4l2_plane_pix_format* plane_fmt; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_WIDTH ; 
 unsigned int MAX_ZOOM ; 
 scalar_t__ V4L2_COLORSPACE_BT2020 ; 
 scalar_t__ V4L2_COLORSPACE_OPRGB ; 
 scalar_t__ V4L2_COLORSPACE_REC709 ; 
 scalar_t__ V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_COLORSPACE_SRGB ; 
 int V4L2_DV_FL_IS_CE_VIDEO ; 
 scalar_t__ V4L2_FIELD_HAS_T_OR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_LIM_RANGE ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  dprintk (struct vivid_dev*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_rect_set_max_size (struct v4l2_rect*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  v4l2_rect_set_min_size (struct v4l2_rect*,struct v4l2_rect*) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_field_out (struct vivid_dev*,int /*<<< orphan*/ ) ; 
 struct vivid_fmt* vivid_get_format (struct vivid_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ vivid_is_svid_out (struct vivid_dev*) ; 
 struct v4l2_rect vivid_max_rect ; 
 struct v4l2_rect vivid_min_rect ; 

int vivid_try_fmt_vid_out(struct file *file, void *priv,
			struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct v4l2_bt_timings *bt = &dev->dv_timings_out.bt;
	struct v4l2_pix_format_mplane *mp = &f->fmt.pix_mp;
	struct v4l2_plane_pix_format *pfmt = mp->plane_fmt;
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

	mp->field = vivid_field_out(dev, mp->field);
	if (vivid_is_svid_out(dev)) {
		w = 720;
		h = (dev->std_out & V4L2_STD_525_60) ? 480 : 576;
	} else {
		w = dev->sink_rect.width;
		h = dev->sink_rect.height;
	}
	if (V4L2_FIELD_HAS_T_OR_B(mp->field))
		factor = 2;
	if (!dev->has_scaler_out && !dev->has_crop_out && !dev->has_compose_out) {
		mp->width = w;
		mp->height = h / factor;
	} else {
		struct v4l2_rect r = { 0, 0, mp->width, mp->height * factor };

		v4l2_rect_set_min_size(&r, &vivid_min_rect);
		v4l2_rect_set_max_size(&r, &vivid_max_rect);
		if (dev->has_scaler_out && !dev->has_crop_out) {
			struct v4l2_rect max_r = { 0, 0, MAX_ZOOM * w, MAX_ZOOM * h };

			v4l2_rect_set_max_size(&r, &max_r);
		} else if (!dev->has_scaler_out && dev->has_compose_out && !dev->has_crop_out) {
			v4l2_rect_set_max_size(&r, &dev->sink_rect);
		} else if (!dev->has_scaler_out && !dev->has_compose_out) {
			v4l2_rect_set_min_size(&r, &dev->sink_rect);
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

	mp->xfer_func = V4L2_XFER_FUNC_DEFAULT;
	mp->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	mp->quantization = V4L2_QUANTIZATION_DEFAULT;
	if (vivid_is_svid_out(dev)) {
		mp->colorspace = V4L2_COLORSPACE_SMPTE170M;
	} else if (dev->dvi_d_out || !(bt->flags & V4L2_DV_FL_IS_CE_VIDEO)) {
		mp->colorspace = V4L2_COLORSPACE_SRGB;
		if (dev->dvi_d_out)
			mp->quantization = V4L2_QUANTIZATION_LIM_RANGE;
	} else if (bt->width == 720 && bt->height <= 576) {
		mp->colorspace = V4L2_COLORSPACE_SMPTE170M;
	} else if (mp->colorspace != V4L2_COLORSPACE_SMPTE170M &&
		   mp->colorspace != V4L2_COLORSPACE_REC709 &&
		   mp->colorspace != V4L2_COLORSPACE_OPRGB &&
		   mp->colorspace != V4L2_COLORSPACE_BT2020 &&
		   mp->colorspace != V4L2_COLORSPACE_SRGB) {
		mp->colorspace = V4L2_COLORSPACE_REC709;
	}
	memset(mp->reserved, 0, sizeof(mp->reserved));
	return 0;
}