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
struct v4l2_rect {int width; int height; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_2__ rect; } ;
struct camif_vp {int rotation; TYPE_3__ out_frame; TYPE_1__* camif; } ;
struct camif_scaler {int pre_h_ratio; int h_shift; int pre_v_ratio; int v_shift; int pre_dst_width; int pre_dst_height; int main_h_ratio; int main_v_ratio; int scaleup_h; int scaleup_v; scalar_t__ copy; } ;
struct TYPE_4__ {struct v4l2_rect camif_crop; } ;

/* Variables and functions */
 int camif_get_scaler_factor (int,int,int*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,...) ; 
 int /*<<< orphan*/  swap (int,int) ; 

int s3c_camif_get_scaler_config(struct camif_vp *vp,
				struct camif_scaler *scaler)
{
	struct v4l2_rect *camif_crop = &vp->camif->camif_crop;
	int source_x = camif_crop->width;
	int source_y = camif_crop->height;
	int target_x = vp->out_frame.rect.width;
	int target_y = vp->out_frame.rect.height;
	int ret;

	if (vp->rotation == 90 || vp->rotation == 270)
		swap(target_x, target_y);

	ret = camif_get_scaler_factor(source_x, target_x, &scaler->pre_h_ratio,
				      &scaler->h_shift);
	if (ret < 0)
		return ret;

	ret = camif_get_scaler_factor(source_y, target_y, &scaler->pre_v_ratio,
				      &scaler->v_shift);
	if (ret < 0)
		return ret;

	scaler->pre_dst_width = source_x / scaler->pre_h_ratio;
	scaler->pre_dst_height = source_y / scaler->pre_v_ratio;

	scaler->main_h_ratio = (source_x << 8) / (target_x << scaler->h_shift);
	scaler->main_v_ratio = (source_y << 8) / (target_y << scaler->v_shift);

	scaler->scaleup_h = (target_x >= source_x);
	scaler->scaleup_v = (target_y >= source_y);

	scaler->copy = 0;

	pr_debug("H: ratio: %u, shift: %u. V: ratio: %u, shift: %u.\n",
		 scaler->pre_h_ratio, scaler->h_shift,
		 scaler->pre_v_ratio, scaler->v_shift);

	pr_debug("Source: %dx%d, Target: %dx%d, scaleup_h/v: %d/%d\n",
		 source_x, source_y, target_x, target_y,
		 scaler->scaleup_h, scaler->scaleup_v);

	return 0;
}