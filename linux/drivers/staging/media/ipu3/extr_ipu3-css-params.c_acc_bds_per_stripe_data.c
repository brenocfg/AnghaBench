#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct imgu_css_pipe {TYPE_11__* rect; } ;
struct imgu_css {struct imgu_css_pipe* pipes; } ;
struct TYPE_22__ {TYPE_8__* aligned_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  out_frame_width; } ;
struct TYPE_15__ {TYPE_3__ hor_ctrl0; } ;
struct TYPE_12__ {TYPE_9__ per_stripe; TYPE_2__ hor; } ;
struct TYPE_18__ {TYPE_4__* down_scaled_stripes; } ;
struct imgu_abi_acc_param {TYPE_10__ bds; TYPE_5__ stripe; } ;
struct TYPE_19__ {int /*<<< orphan*/  out_frame_height; int /*<<< orphan*/  out_frame_width; } ;
struct TYPE_14__ {scalar_t__ hor_crop_end; scalar_t__ hor_crop_start; scalar_t__ hor_crop_en; } ;
struct TYPE_20__ {TYPE_6__ ver_ctrl1; TYPE_3__ hor_ctrl0; TYPE_1__ crop; } ;
struct TYPE_21__ {TYPE_7__ data; } ;
struct TYPE_17__ {int /*<<< orphan*/  width; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; } ;

/* Variables and functions */
 size_t IPU3_CSS_RECT_BDS ; 

__attribute__((used)) static void acc_bds_per_stripe_data(struct imgu_css *css,
				    struct imgu_abi_acc_param *acc,
				    const int i, unsigned int pipe)
{
	struct imgu_css_pipe *css_pipe = &css->pipes[pipe];

	acc->bds.per_stripe.aligned_data[i].data.crop.hor_crop_en = 0;
	acc->bds.per_stripe.aligned_data[i].data.crop.hor_crop_start = 0;
	acc->bds.per_stripe.aligned_data[i].data.crop.hor_crop_end = 0;
	acc->bds.per_stripe.aligned_data[i].data.hor_ctrl0 =
		acc->bds.hor.hor_ctrl0;
	acc->bds.per_stripe.aligned_data[i].data.hor_ctrl0.out_frame_width =
		acc->stripe.down_scaled_stripes[i].width;
	acc->bds.per_stripe.aligned_data[i].data.ver_ctrl1.out_frame_width =
		acc->stripe.down_scaled_stripes[i].width;
	acc->bds.per_stripe.aligned_data[i].data.ver_ctrl1.out_frame_height =
		css_pipe->rect[IPU3_CSS_RECT_BDS].height;
}