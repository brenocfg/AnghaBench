#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gsc_variant {int dummy; } ;
struct gsc_scaler {int main_hratio; int main_vratio; int /*<<< orphan*/  pre_vratio; int /*<<< orphan*/  pre_hratio; int /*<<< orphan*/  pre_shfactor; } ;
struct TYPE_10__ {int width; int height; } ;
struct gsc_frame {TYPE_5__ crop; } ;
struct TYPE_9__ {TYPE_3__* rotate; } ;
struct gsc_ctx {TYPE_4__ gsc_ctrls; int /*<<< orphan*/  out_path; TYPE_2__* gsc_dev; struct gsc_frame d_frame; struct gsc_frame s_frame; struct gsc_scaler scaler; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int val; } ;
struct TYPE_7__ {TYPE_1__* pdev; struct gsc_variant* variant; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int gsc_cal_prescaler_ratio (struct gsc_variant*,int,int,int /*<<< orphan*/ *) ; 
 int gsc_check_scaler_ratio (struct gsc_variant*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_check_src_scale_info (struct gsc_variant*,struct gsc_frame*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gsc_get_prescaler_shfactor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int gsc_set_scaler_info(struct gsc_ctx *ctx)
{
	struct gsc_scaler *sc = &ctx->scaler;
	struct gsc_frame *s_frame = &ctx->s_frame;
	struct gsc_frame *d_frame = &ctx->d_frame;
	struct gsc_variant *variant = ctx->gsc_dev->variant;
	struct device *dev = &ctx->gsc_dev->pdev->dev;
	int tx, ty;
	int ret;

	ret = gsc_check_scaler_ratio(variant, s_frame->crop.width,
		s_frame->crop.height, d_frame->crop.width, d_frame->crop.height,
		ctx->gsc_ctrls.rotate->val, ctx->out_path);
	if (ret) {
		pr_err("out of scaler range");
		return ret;
	}

	if (ctx->gsc_ctrls.rotate->val == 90 ||
	    ctx->gsc_ctrls.rotate->val == 270) {
		ty = d_frame->crop.width;
		tx = d_frame->crop.height;
	} else {
		tx = d_frame->crop.width;
		ty = d_frame->crop.height;
	}

	if (tx <= 0 || ty <= 0) {
		dev_err(dev, "Invalid target size: %dx%d", tx, ty);
		return -EINVAL;
	}

	ret = gsc_cal_prescaler_ratio(variant, s_frame->crop.width,
				      tx, &sc->pre_hratio);
	if (ret) {
		pr_err("Horizontal scale ratio is out of range");
		return ret;
	}

	ret = gsc_cal_prescaler_ratio(variant, s_frame->crop.height,
				      ty, &sc->pre_vratio);
	if (ret) {
		pr_err("Vertical scale ratio is out of range");
		return ret;
	}

	gsc_check_src_scale_info(variant, s_frame, &sc->pre_hratio,
				 tx, ty, &sc->pre_vratio);

	gsc_get_prescaler_shfactor(sc->pre_hratio, sc->pre_vratio,
				   &sc->pre_shfactor);

	sc->main_hratio = (s_frame->crop.width << 16) / tx;
	sc->main_vratio = (s_frame->crop.height << 16) / ty;

	pr_debug("scaler input/output size : sx = %d, sy = %d, tx = %d, ty = %d",
			s_frame->crop.width, s_frame->crop.height, tx, ty);
	pr_debug("scaler ratio info : pre_shfactor : %d, pre_h : %d",
			sc->pre_shfactor, sc->pre_hratio);
	pr_debug("pre_v :%d, main_h : %d, main_v : %d",
			sc->pre_vratio, sc->main_hratio, sc->main_vratio);

	return 0;
}