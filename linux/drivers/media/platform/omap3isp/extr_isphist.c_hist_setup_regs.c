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
typedef  int u32 ;
struct omap3isp_hist_config {int cfa; int* wg; int num_regions; int hist_bins; int /*<<< orphan*/  buf_size; TYPE_1__* region; } ;
struct ispstat {scalar_t__ state; int /*<<< orphan*/  buf_size; scalar_t__ inc_config; int /*<<< orphan*/  config_counter; scalar_t__ update; struct isp_device* isp; } ;
struct isp_device {int dummy; } ;
struct TYPE_2__ {int h_start; int h_end; int v_start; int v_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPHIST_CNT ; 
 int ISPHIST_CNT_BINS_SHIFT ; 
 int ISPHIST_CNT_CFA_SHIFT ; 
 int ISPHIST_CNT_SHIFT_SHIFT ; 
 int /*<<< orphan*/  ISPHIST_IN_BIT_WIDTH_CCDC ; 
 int /*<<< orphan*/  ISPHIST_R0_HORZ ; 
 int /*<<< orphan*/  ISPHIST_R0_VERT ; 
 int /*<<< orphan*/  ISPHIST_R1_HORZ ; 
 int /*<<< orphan*/  ISPHIST_R1_VERT ; 
 int /*<<< orphan*/  ISPHIST_R2_HORZ ; 
 int /*<<< orphan*/  ISPHIST_R2_VERT ; 
 int /*<<< orphan*/  ISPHIST_R3_HORZ ; 
 int /*<<< orphan*/  ISPHIST_R3_VERT ; 
 int ISPHIST_REG_END_SHIFT ; 
 int ISPHIST_REG_START_SHIFT ; 
 int /*<<< orphan*/  ISPHIST_WB_GAIN ; 
 int ISPHIST_WB_GAIN_WG00_SHIFT ; 
 int ISPHIST_WB_GAIN_WG01_SHIFT ; 
 int ISPHIST_WB_GAIN_WG02_SHIFT ; 
 int ISPHIST_WB_GAIN_WG03_SHIFT ; 
 scalar_t__ ISPSTAT_DISABLED ; 
 scalar_t__ ISPSTAT_DISABLING ; 
#define  OMAP3ISP_HIST_BINS_128 130 
#define  OMAP3ISP_HIST_BINS_256 129 
#define  OMAP3ISP_HIST_BINS_64 128 
 int OMAP3ISP_HIST_CFA_BAYER ; 
 int OMAP3ISP_HIST_MAX_REGIONS ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_HIST ; 
 int /*<<< orphan*/  hist_reset_mem (struct ispstat*) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hist_setup_regs(struct ispstat *hist, void *priv)
{
	struct isp_device *isp = hist->isp;
	struct omap3isp_hist_config *conf = priv;
	int c;
	u32 cnt;
	u32 wb_gain;
	u32 reg_hor[OMAP3ISP_HIST_MAX_REGIONS];
	u32 reg_ver[OMAP3ISP_HIST_MAX_REGIONS];

	if (!hist->update || hist->state == ISPSTAT_DISABLED ||
	    hist->state == ISPSTAT_DISABLING)
		return;

	cnt = conf->cfa << ISPHIST_CNT_CFA_SHIFT;

	wb_gain = conf->wg[0] << ISPHIST_WB_GAIN_WG00_SHIFT;
	wb_gain |= conf->wg[1] << ISPHIST_WB_GAIN_WG01_SHIFT;
	wb_gain |= conf->wg[2] << ISPHIST_WB_GAIN_WG02_SHIFT;
	if (conf->cfa == OMAP3ISP_HIST_CFA_BAYER)
		wb_gain |= conf->wg[3] << ISPHIST_WB_GAIN_WG03_SHIFT;

	/* Regions size and position */
	for (c = 0; c < OMAP3ISP_HIST_MAX_REGIONS; c++) {
		if (c < conf->num_regions) {
			reg_hor[c] = (conf->region[c].h_start <<
				     ISPHIST_REG_START_SHIFT)
				   | (conf->region[c].h_end <<
				     ISPHIST_REG_END_SHIFT);
			reg_ver[c] = (conf->region[c].v_start <<
				     ISPHIST_REG_START_SHIFT)
				   | (conf->region[c].v_end <<
				     ISPHIST_REG_END_SHIFT);
		} else {
			reg_hor[c] = 0;
			reg_ver[c] = 0;
		}
	}

	cnt |= conf->hist_bins << ISPHIST_CNT_BINS_SHIFT;
	switch (conf->hist_bins) {
	case OMAP3ISP_HIST_BINS_256:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 8) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		break;
	case OMAP3ISP_HIST_BINS_128:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 7) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		break;
	case OMAP3ISP_HIST_BINS_64:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 6) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		break;
	default: /* OMAP3ISP_HIST_BINS_32 */
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 5) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		break;
	}

	hist_reset_mem(hist);

	isp_reg_writel(isp, cnt, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT);
	isp_reg_writel(isp, wb_gain,  OMAP3_ISP_IOMEM_HIST, ISPHIST_WB_GAIN);
	isp_reg_writel(isp, reg_hor[0], OMAP3_ISP_IOMEM_HIST, ISPHIST_R0_HORZ);
	isp_reg_writel(isp, reg_ver[0], OMAP3_ISP_IOMEM_HIST, ISPHIST_R0_VERT);
	isp_reg_writel(isp, reg_hor[1], OMAP3_ISP_IOMEM_HIST, ISPHIST_R1_HORZ);
	isp_reg_writel(isp, reg_ver[1], OMAP3_ISP_IOMEM_HIST, ISPHIST_R1_VERT);
	isp_reg_writel(isp, reg_hor[2], OMAP3_ISP_IOMEM_HIST, ISPHIST_R2_HORZ);
	isp_reg_writel(isp, reg_ver[2], OMAP3_ISP_IOMEM_HIST, ISPHIST_R2_VERT);
	isp_reg_writel(isp, reg_hor[3], OMAP3_ISP_IOMEM_HIST, ISPHIST_R3_HORZ);
	isp_reg_writel(isp, reg_ver[3], OMAP3_ISP_IOMEM_HIST, ISPHIST_R3_VERT);

	hist->update = 0;
	hist->config_counter += hist->inc_config;
	hist->inc_config = 0;
	hist->buf_size = conf->buf_size;
}