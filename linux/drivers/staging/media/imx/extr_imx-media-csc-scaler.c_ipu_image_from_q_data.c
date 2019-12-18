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
struct v4l2_pix_format {scalar_t__ ycbcr_enc; scalar_t__ quantization; int /*<<< orphan*/  colorspace; } ;
struct ipu_image {int /*<<< orphan*/  rect; struct v4l2_pix_format pix; } ;
struct ipu_csc_scaler_q_data {int /*<<< orphan*/  rect; struct v4l2_pix_format cur_fmt; } ;

/* Variables and functions */
 void* V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_QUANTIZATION_DEFAULT ; 
 scalar_t__ V4L2_YCBCR_ENC_DEFAULT ; 

__attribute__((used)) static void ipu_image_from_q_data(struct ipu_image *im,
				  struct ipu_csc_scaler_q_data *q_data)
{
	struct v4l2_pix_format *fmt = &q_data->cur_fmt;

	im->pix = *fmt;
	if (fmt->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT)
		im->pix.ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	if (fmt->quantization == V4L2_QUANTIZATION_DEFAULT)
		im->pix.ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	im->rect = q_data->rect;
}