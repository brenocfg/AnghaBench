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
struct v4l2_rect {int height; int top; int width; int left; } ;
struct v4l2_pix_format {scalar_t__ pixelformat; int height; int width; } ;
struct omap_vout_device {int mirror; int cropped_offset; int ps; int vr_ps; int line_length; TYPE_1__* vrfb_context; struct v4l2_pix_format pix; struct v4l2_rect crop; } ;
typedef  enum dss_rotation { ____Placeholder_dss_rotation } dss_rotation ;
struct TYPE_2__ {int yoffset; int bytespp; int xoffset; } ;

/* Variables and functions */
 int MAX_PIXELS_PER_LINE ; 
 scalar_t__ V4L2_PIX_FMT_RGB24 ; 
 scalar_t__ V4L2_PIX_FMT_RGB32 ; 
 scalar_t__ V4L2_PIX_FMT_UYVY ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int calc_rotation (struct omap_vout_device*) ; 
#define  dss_rotation_0_degree 131 
#define  dss_rotation_180_degree 130 
#define  dss_rotation_270_degree 129 
#define  dss_rotation_90_degree 128 
 scalar_t__ is_rotation_enabled (struct omap_vout_device*) ; 

void omap_vout_calculate_vrfb_offset(struct omap_vout_device *vout)
{
	enum dss_rotation rotation;
	bool mirroring = vout->mirror;
	struct v4l2_rect *crop = &vout->crop;
	struct v4l2_pix_format *pix = &vout->pix;
	int *cropped_offset = &vout->cropped_offset;
	int vr_ps = 1, ps = 2, temp_ps = 2;
	int offset = 0, ctop = 0, cleft = 0, line_length = 0;

	rotation = calc_rotation(vout);

	if (V4L2_PIX_FMT_YUYV == pix->pixelformat ||
			V4L2_PIX_FMT_UYVY == pix->pixelformat) {
		if (is_rotation_enabled(vout)) {
			/*
			 * ps    - Actual pixel size for YUYV/UYVY for
			 *         VRFB/Mirroring is 4 bytes
			 * vr_ps - Virtually pixel size for YUYV/UYVY is
			 *         2 bytes
			 */
			ps = 4;
			vr_ps = 2;
		} else {
			ps = 2;	/* otherwise the pixel size is 2 byte */
		}
	} else if (V4L2_PIX_FMT_RGB32 == pix->pixelformat) {
		ps = 4;
	} else if (V4L2_PIX_FMT_RGB24 == pix->pixelformat) {
		ps = 3;
	}
	vout->ps = ps;
	vout->vr_ps = vr_ps;

	if (is_rotation_enabled(vout)) {
		line_length = MAX_PIXELS_PER_LINE;
		ctop = (pix->height - crop->height) - crop->top;
		cleft = (pix->width - crop->width) - crop->left;
	} else {
		line_length = pix->width;
	}
	vout->line_length = line_length;
	switch (rotation) {
	case dss_rotation_90_degree:
		offset = vout->vrfb_context[0].yoffset *
			vout->vrfb_context[0].bytespp;
		temp_ps = ps / vr_ps;
		if (!mirroring) {
			*cropped_offset = offset + line_length *
				temp_ps * cleft + crop->top * temp_ps;
		} else {
			*cropped_offset = offset + line_length * temp_ps *
				cleft + crop->top * temp_ps + (line_length *
				((crop->width / (vr_ps)) - 1) * ps);
		}
		break;
	case dss_rotation_180_degree:
		offset = ((MAX_PIXELS_PER_LINE * vout->vrfb_context[0].yoffset *
			vout->vrfb_context[0].bytespp) +
			(vout->vrfb_context[0].xoffset *
			vout->vrfb_context[0].bytespp));
		if (!mirroring) {
			*cropped_offset = offset + (line_length * ps * ctop) +
				(cleft / vr_ps) * ps;

		} else {
			*cropped_offset = offset + (line_length * ps * ctop) +
				(cleft / vr_ps) * ps + (line_length *
				(crop->height - 1) * ps);
		}
		break;
	case dss_rotation_270_degree:
		offset = MAX_PIXELS_PER_LINE * vout->vrfb_context[0].xoffset *
			vout->vrfb_context[0].bytespp;
		temp_ps = ps / vr_ps;
		if (!mirroring) {
			*cropped_offset = offset + line_length *
			    temp_ps * crop->left + ctop * ps;
		} else {
			*cropped_offset = offset + line_length *
				temp_ps * crop->left + ctop * ps +
				(line_length * ((crop->width / vr_ps) - 1) *
				 ps);
		}
		break;
	case dss_rotation_0_degree:
		if (!mirroring) {
			*cropped_offset = (line_length * ps) *
				crop->top + (crop->left / vr_ps) * ps;
		} else {
			*cropped_offset = (line_length * ps) *
				crop->top + (crop->left / vr_ps) * ps +
				(line_length * (crop->height - 1) * ps);
		}
		break;
	default:
		*cropped_offset = (line_length * ps * crop->top) /
			vr_ps + (crop->left * ps) / vr_ps +
			((crop->width / vr_ps) - 1) * ps;
		break;
	}
}