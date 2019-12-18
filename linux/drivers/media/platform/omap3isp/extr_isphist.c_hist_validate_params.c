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
typedef  scalar_t__ u32 ;
struct omap3isp_hist_config {scalar_t__ cfa; int num_regions; scalar_t__ buf_size; int /*<<< orphan*/  hist_bins; TYPE_1__* region; } ;
struct ispstat {int dummy; } ;
struct TYPE_2__ {int h_start; int h_end; int v_start; int v_end; } ;

/* Variables and functions */
 int EINVAL ; 
 int ISPHIST_REG_START_END_MASK ; 
 int /*<<< orphan*/  OMAP3ISP_HIST_BINS_128 ; 
 int /*<<< orphan*/  OMAP3ISP_HIST_BINS_256 ; 
 int /*<<< orphan*/  OMAP3ISP_HIST_BINS_64 ; 
 scalar_t__ OMAP3ISP_HIST_CFA_FOVEONX3 ; 
 scalar_t__ OMAP3ISP_HIST_MAX_BUF_SIZE ; 
 int OMAP3ISP_HIST_MAX_REGIONS ; 
 int OMAP3ISP_HIST_MIN_REGIONS ; 
 scalar_t__ hist_get_buf_size (struct omap3isp_hist_config*) ; 

__attribute__((used)) static int hist_validate_params(struct ispstat *hist, void *new_conf)
{
	struct omap3isp_hist_config *user_cfg = new_conf;
	int c;
	u32 buf_size;

	if (user_cfg->cfa > OMAP3ISP_HIST_CFA_FOVEONX3)
		return -EINVAL;

	/* Regions size and position */

	if ((user_cfg->num_regions < OMAP3ISP_HIST_MIN_REGIONS) ||
	    (user_cfg->num_regions > OMAP3ISP_HIST_MAX_REGIONS))
		return -EINVAL;

	/* Regions */
	for (c = 0; c < user_cfg->num_regions; c++) {
		if (user_cfg->region[c].h_start & ~ISPHIST_REG_START_END_MASK)
			return -EINVAL;
		if (user_cfg->region[c].h_end & ~ISPHIST_REG_START_END_MASK)
			return -EINVAL;
		if (user_cfg->region[c].v_start & ~ISPHIST_REG_START_END_MASK)
			return -EINVAL;
		if (user_cfg->region[c].v_end & ~ISPHIST_REG_START_END_MASK)
			return -EINVAL;
		if (user_cfg->region[c].h_start > user_cfg->region[c].h_end)
			return -EINVAL;
		if (user_cfg->region[c].v_start > user_cfg->region[c].v_end)
			return -EINVAL;
	}

	switch (user_cfg->num_regions) {
	case 1:
		if (user_cfg->hist_bins > OMAP3ISP_HIST_BINS_256)
			return -EINVAL;
		break;
	case 2:
		if (user_cfg->hist_bins > OMAP3ISP_HIST_BINS_128)
			return -EINVAL;
		break;
	default: /* 3 or 4 */
		if (user_cfg->hist_bins > OMAP3ISP_HIST_BINS_64)
			return -EINVAL;
		break;
	}

	buf_size = hist_get_buf_size(user_cfg);
	if (buf_size > user_cfg->buf_size)
		/* User's buf_size request wasn't enough */
		user_cfg->buf_size = buf_size;
	else if (user_cfg->buf_size > OMAP3ISP_HIST_MAX_BUF_SIZE)
		user_cfg->buf_size = OMAP3ISP_HIST_MAX_BUF_SIZE;

	return 0;
}