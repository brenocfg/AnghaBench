#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap3isp_hist_config {scalar_t__ cfa; scalar_t__ num_acc_frames; scalar_t__ hist_bins; scalar_t__* wg; int num_regions; TYPE_1__* region; } ;
struct ispstat {struct omap3isp_hist_config* priv; } ;
struct TYPE_2__ {scalar_t__ h_start; scalar_t__ h_end; scalar_t__ v_start; scalar_t__ v_end; } ;

/* Variables and functions */
 scalar_t__ OMAP3ISP_HIST_CFA_FOVEONX3 ; 
 int OMAP3ISP_HIST_MAX_WG ; 

__attribute__((used)) static int hist_comp_params(struct ispstat *hist,
			    struct omap3isp_hist_config *user_cfg)
{
	struct omap3isp_hist_config *cur_cfg = hist->priv;
	int c;

	if (cur_cfg->cfa != user_cfg->cfa)
		return 1;

	if (cur_cfg->num_acc_frames != user_cfg->num_acc_frames)
		return 1;

	if (cur_cfg->hist_bins != user_cfg->hist_bins)
		return 1;

	for (c = 0; c < OMAP3ISP_HIST_MAX_WG; c++) {
		if (c == 3 && user_cfg->cfa == OMAP3ISP_HIST_CFA_FOVEONX3)
			break;
		else if (cur_cfg->wg[c] != user_cfg->wg[c])
			return 1;
	}

	if (cur_cfg->num_regions != user_cfg->num_regions)
		return 1;

	/* Regions */
	for (c = 0; c < user_cfg->num_regions; c++) {
		if (cur_cfg->region[c].h_start != user_cfg->region[c].h_start)
			return 1;
		if (cur_cfg->region[c].h_end != user_cfg->region[c].h_end)
			return 1;
		if (cur_cfg->region[c].v_start != user_cfg->region[c].v_start)
			return 1;
		if (cur_cfg->region[c].v_end != user_cfg->region[c].v_end)
			return 1;
	}

	return 0;
}