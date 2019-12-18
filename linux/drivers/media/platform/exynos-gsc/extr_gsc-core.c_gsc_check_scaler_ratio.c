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
struct gsc_variant {int sc_down_max; int local_sc_down; int sc_up_max; } ;

/* Variables and functions */
 int EINVAL ; 
 int GSC_DMA ; 

int gsc_check_scaler_ratio(struct gsc_variant *var, int sw, int sh, int dw,
			   int dh, int rot, int out_path)
{
	int tmp_w, tmp_h, sc_down_max;

	if (out_path == GSC_DMA)
		sc_down_max = var->sc_down_max;
	else
		sc_down_max = var->local_sc_down;

	if (rot == 90 || rot == 270) {
		tmp_w = dh;
		tmp_h = dw;
	} else {
		tmp_w = dw;
		tmp_h = dh;
	}

	if ((sw / tmp_w) > sc_down_max ||
	    (sh / tmp_h) > sc_down_max ||
	    (tmp_w / sw) > var->sc_up_max ||
	    (tmp_h / sh) > var->sc_up_max)
		return -EINVAL;

	return 0;
}