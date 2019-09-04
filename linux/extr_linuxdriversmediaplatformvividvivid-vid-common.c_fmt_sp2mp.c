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
struct v4l2_plane_pix_format {int /*<<< orphan*/  reserved; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  sizeimage; } ;
struct v4l2_pix_format_mplane {int num_planes; int /*<<< orphan*/  flags; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  reserved; struct v4l2_plane_pix_format* plane_fmt; } ;
struct v4l2_pix_format {int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  flags; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ V4L2_CAP_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void fmt_sp2mp(const struct v4l2_format *sp_fmt, struct v4l2_format *mp_fmt)
{
	struct v4l2_pix_format_mplane *mp = &mp_fmt->fmt.pix_mp;
	struct v4l2_plane_pix_format *ppix = &mp->plane_fmt[0];
	const struct v4l2_pix_format *pix = &sp_fmt->fmt.pix;
	bool is_out = sp_fmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT;

	memset(mp->reserved, 0, sizeof(mp->reserved));
	mp_fmt->type = is_out ? V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE :
			   V4L2_CAP_VIDEO_CAPTURE_MPLANE;
	mp->width = pix->width;
	mp->height = pix->height;
	mp->pixelformat = pix->pixelformat;
	mp->field = pix->field;
	mp->colorspace = pix->colorspace;
	mp->xfer_func = pix->xfer_func;
	/* Also copies hsv_enc */
	mp->ycbcr_enc = pix->ycbcr_enc;
	mp->quantization = pix->quantization;
	mp->num_planes = 1;
	mp->flags = pix->flags;
	ppix->sizeimage = pix->sizeimage;
	ppix->bytesperline = pix->bytesperline;
	memset(ppix->reserved, 0, sizeof(ppix->reserved));
}