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
typedef  int u32 ;
struct gsc_variant {int poly_sc_down_max; int pre_sc_down_max; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int gsc_cal_prescaler_ratio(struct gsc_variant *var, u32 src, u32 dst,
								u32 *ratio)
{
	if ((dst > src) || (dst >= src / var->poly_sc_down_max)) {
		*ratio = 1;
		return 0;
	}

	if ((src / var->poly_sc_down_max / var->pre_sc_down_max) > dst) {
		pr_err("Exceeded maximum downscaling ratio (1/16))");
		return -EINVAL;
	}

	*ratio = (dst > (src / 8)) ? 2 : 4;

	return 0;
}