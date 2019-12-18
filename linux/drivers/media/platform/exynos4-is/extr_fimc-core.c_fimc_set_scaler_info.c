#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fimc_variant {scalar_t__ has_mainscaler_ext; } ;
struct fimc_scaler {int real_width; int real_height; int pre_hratio; int hfactor; int pre_vratio; int vfactor; int pre_dst_width; int pre_dst_height; int main_hratio; int main_vratio; int scaleup_h; int scaleup_v; int copy_mode; } ;
struct fimc_frame {int width; int height; TYPE_3__* fmt; } ;
struct fimc_ctx {int rotation; struct fimc_frame d_frame; struct fimc_frame s_frame; struct fimc_scaler scaler; TYPE_2__* fimc_dev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {scalar_t__ color; } ;
struct TYPE_5__ {TYPE_1__* pdev; struct fimc_variant* variant; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int fimc_get_scaler_factor (int,int,int*,int*) ; 

int fimc_set_scaler_info(struct fimc_ctx *ctx)
{
	const struct fimc_variant *variant = ctx->fimc_dev->variant;
	struct device *dev = &ctx->fimc_dev->pdev->dev;
	struct fimc_scaler *sc = &ctx->scaler;
	struct fimc_frame *s_frame = &ctx->s_frame;
	struct fimc_frame *d_frame = &ctx->d_frame;
	int tx, ty, sx, sy;
	int ret;

	if (ctx->rotation == 90 || ctx->rotation == 270) {
		ty = d_frame->width;
		tx = d_frame->height;
	} else {
		tx = d_frame->width;
		ty = d_frame->height;
	}
	if (tx <= 0 || ty <= 0) {
		dev_err(dev, "Invalid target size: %dx%d\n", tx, ty);
		return -EINVAL;
	}

	sx = s_frame->width;
	sy = s_frame->height;
	if (sx <= 0 || sy <= 0) {
		dev_err(dev, "Invalid source size: %dx%d\n", sx, sy);
		return -EINVAL;
	}
	sc->real_width = sx;
	sc->real_height = sy;

	ret = fimc_get_scaler_factor(sx, tx, &sc->pre_hratio, &sc->hfactor);
	if (ret)
		return ret;

	ret = fimc_get_scaler_factor(sy, ty,  &sc->pre_vratio, &sc->vfactor);
	if (ret)
		return ret;

	sc->pre_dst_width = sx / sc->pre_hratio;
	sc->pre_dst_height = sy / sc->pre_vratio;

	if (variant->has_mainscaler_ext) {
		sc->main_hratio = (sx << 14) / (tx << sc->hfactor);
		sc->main_vratio = (sy << 14) / (ty << sc->vfactor);
	} else {
		sc->main_hratio = (sx << 8) / (tx << sc->hfactor);
		sc->main_vratio = (sy << 8) / (ty << sc->vfactor);

	}

	sc->scaleup_h = (tx >= sx) ? 1 : 0;
	sc->scaleup_v = (ty >= sy) ? 1 : 0;

	/* check to see if input and output size/format differ */
	if (s_frame->fmt->color == d_frame->fmt->color
		&& s_frame->width == d_frame->width
		&& s_frame->height == d_frame->height)
		sc->copy_mode = 1;
	else
		sc->copy_mode = 0;

	return 0;
}