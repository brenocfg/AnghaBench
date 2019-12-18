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
struct TYPE_4__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct tpg_data {scalar_t__ color_enc; int /*<<< orphan*/  real_rgb_range; int /*<<< orphan*/  rgb_range; int /*<<< orphan*/  real_quantization; int /*<<< orphan*/  quantization; int /*<<< orphan*/  real_ycbcr_enc; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  real_hsv_enc; int /*<<< orphan*/  hsv_enc; int /*<<< orphan*/  real_xfer_func; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  colorspace; TYPE_2__ compose; TYPE_1__ crop; int /*<<< orphan*/  field; int /*<<< orphan*/  src_height; int /*<<< orphan*/  src_width; } ;

/* Variables and functions */
 scalar_t__ TGP_COLOR_ENC_HSV ; 
 scalar_t__ TGP_COLOR_ENC_YCBCR ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  tpg_color_enc_str (scalar_t__) ; 

void tpg_log_status(struct tpg_data *tpg)
{
	pr_info("tpg source WxH: %ux%u (%s)\n",
		tpg->src_width, tpg->src_height,
		tpg_color_enc_str(tpg->color_enc));
	pr_info("tpg field: %u\n", tpg->field);
	pr_info("tpg crop: %ux%u@%dx%d\n", tpg->crop.width, tpg->crop.height,
			tpg->crop.left, tpg->crop.top);
	pr_info("tpg compose: %ux%u@%dx%d\n", tpg->compose.width, tpg->compose.height,
			tpg->compose.left, tpg->compose.top);
	pr_info("tpg colorspace: %d\n", tpg->colorspace);
	pr_info("tpg transfer function: %d/%d\n", tpg->xfer_func, tpg->real_xfer_func);
	if (tpg->color_enc == TGP_COLOR_ENC_HSV)
		pr_info("tpg HSV encoding: %d/%d\n",
			tpg->hsv_enc, tpg->real_hsv_enc);
	else if (tpg->color_enc == TGP_COLOR_ENC_YCBCR)
		pr_info("tpg Y'CbCr encoding: %d/%d\n",
			tpg->ycbcr_enc, tpg->real_ycbcr_enc);
	pr_info("tpg quantization: %d/%d\n", tpg->quantization, tpg->real_quantization);
	pr_info("tpg RGB range: %d/%d\n", tpg->rgb_range, tpg->real_rgb_range);
}