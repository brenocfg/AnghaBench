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
struct v4l2_pix_format {int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; } ;
struct rvin_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVIN_DEFAULT_COLORSPACE ; 
 int /*<<< orphan*/  V4L2_MAP_QUANTIZATION_DEFAULT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_XFER_FUNC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_format_align (struct rvin_dev*,struct v4l2_pix_format*) ; 

__attribute__((used)) static void rvin_mc_try_format(struct rvin_dev *vin,
			       struct v4l2_pix_format *pix)
{
	/*
	 * The V4L2 specification clearly documents the colorspace fields
	 * as being set by drivers for capture devices. Using the values
	 * supplied by userspace thus wouldn't comply with the API. Until
	 * the API is updated force fixed values.
	 */
	pix->colorspace = RVIN_DEFAULT_COLORSPACE;
	pix->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(pix->colorspace);
	pix->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(pix->colorspace);
	pix->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true, pix->colorspace,
							  pix->ycbcr_enc);

	rvin_format_align(vin, pix);
}