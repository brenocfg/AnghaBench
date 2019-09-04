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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct csc_data {int dummy; } ;
struct colorspace_coeffs {int* sd; int* hd; } ;
typedef  enum v4l2_colorspace { ____Placeholder_v4l2_colorspace } v4l2_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  CSC_BYPASS ; 
 int V4L2_COLORSPACE_REC709 ; 
 int V4L2_COLORSPACE_SMPTE170M ; 
 int V4L2_COLORSPACE_SRGB ; 
 struct colorspace_coeffs* colorspace_coeffs ; 

void csc_set_coeff(struct csc_data *csc, u32 *csc_reg0,
		enum v4l2_colorspace src_colorspace,
		enum v4l2_colorspace dst_colorspace)
{
	u32 *csc_reg5 = csc_reg0 + 5;
	u32 *shadow_csc = csc_reg0;
	struct colorspace_coeffs *sd_hd_coeffs;
	u16 *coeff, *end_coeff;
	enum v4l2_colorspace yuv_colorspace;
	int sel = 0;

	/*
	 * support only graphics data range(full range) for now, a control ioctl
	 * would be nice here
	 */
	/* Y2R */
	if (dst_colorspace == V4L2_COLORSPACE_SRGB &&
			(src_colorspace == V4L2_COLORSPACE_SMPTE170M ||
			src_colorspace == V4L2_COLORSPACE_REC709)) {
		/* Y2R */
		sel = 1;
		yuv_colorspace = src_colorspace;
	} else if ((dst_colorspace == V4L2_COLORSPACE_SMPTE170M ||
			dst_colorspace == V4L2_COLORSPACE_REC709) &&
			src_colorspace == V4L2_COLORSPACE_SRGB) {
		/* R2Y */
		sel = 3;
		yuv_colorspace = dst_colorspace;
	} else {
		*csc_reg5 |= CSC_BYPASS;
		return;
	}

	sd_hd_coeffs = &colorspace_coeffs[sel];

	/* select between SD or HD coefficients */
	if (yuv_colorspace == V4L2_COLORSPACE_SMPTE170M)
		coeff = sd_hd_coeffs->sd;
	else
		coeff = sd_hd_coeffs->hd;

	end_coeff = coeff + 12;

	for (; coeff < end_coeff; coeff += 2)
		*shadow_csc++ = (*(coeff + 1) << 16) | *coeff;
}