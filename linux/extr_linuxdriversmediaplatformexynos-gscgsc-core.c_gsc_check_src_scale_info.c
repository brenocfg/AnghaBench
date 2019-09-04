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
typedef  int u32 ;
struct gsc_variant {int dummy; } ;
struct TYPE_4__ {int width; int height; } ;
struct gsc_frame {TYPE_2__ crop; TYPE_1__* fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int GSC_SC_ALIGN_2 ; 
 int GSC_SC_ALIGN_4 ; 
 int /*<<< orphan*/  gsc_cal_prescaler_ratio (struct gsc_variant*,int,int,int*) ; 
 scalar_t__ is_yuv420 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_yuv422 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

void gsc_check_src_scale_info(struct gsc_variant *var,
				struct gsc_frame *s_frame, u32 *wratio,
				 u32 tx, u32 ty, u32 *hratio)
{
	int remainder = 0, walign, halign;

	if (is_yuv420(s_frame->fmt->color)) {
		walign = GSC_SC_ALIGN_4;
		halign = GSC_SC_ALIGN_4;
	} else if (is_yuv422(s_frame->fmt->color)) {
		walign = GSC_SC_ALIGN_4;
		halign = GSC_SC_ALIGN_2;
	} else {
		walign = GSC_SC_ALIGN_2;
		halign = GSC_SC_ALIGN_2;
	}

	remainder = s_frame->crop.width % (*wratio * walign);
	if (remainder) {
		s_frame->crop.width -= remainder;
		gsc_cal_prescaler_ratio(var, s_frame->crop.width, tx, wratio);
		pr_info("cropped src width size is recalculated from %d to %d",
			s_frame->crop.width + remainder, s_frame->crop.width);
	}

	remainder = s_frame->crop.height % (*hratio * halign);
	if (remainder) {
		s_frame->crop.height -= remainder;
		gsc_cal_prescaler_ratio(var, s_frame->crop.height, ty, hratio);
		pr_info("cropped src height size is recalculated from %d to %d",
			s_frame->crop.height + remainder, s_frame->crop.height);
	}
}