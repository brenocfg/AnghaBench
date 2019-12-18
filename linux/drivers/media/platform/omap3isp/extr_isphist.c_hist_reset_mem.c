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
struct omap3isp_hist_config {int /*<<< orphan*/  num_acc_frames; } ;
struct ispstat {int /*<<< orphan*/  wait_acc_frames; struct omap3isp_hist_config* priv; struct isp_device* isp; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPHIST_ADDR ; 
 int /*<<< orphan*/  ISPHIST_CNT ; 
 int /*<<< orphan*/  ISPHIST_CNT_CLEAR ; 
 int /*<<< orphan*/  ISPHIST_DATA ; 
 int OMAP3ISP_HIST_MEM_SIZE ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_HIST ; 
 int /*<<< orphan*/  isp_reg_clr (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hist_reset_mem(struct ispstat *hist)
{
	struct isp_device *isp = hist->isp;
	struct omap3isp_hist_config *conf = hist->priv;
	unsigned int i;

	isp_reg_writel(isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDR);

	/*
	 * By setting it, the histogram internal buffer is being cleared at the
	 * same time it's being read. This bit must be cleared afterwards.
	 */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CLEAR);

	/*
	 * We'll clear 4 words at each iteration for optimization. It avoids
	 * 3/4 of the jumps. We also know HIST_MEM_SIZE is divisible by 4.
	 */
	for (i = OMAP3ISP_HIST_MEM_SIZE / 4; i > 0; i--) {
		isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
	}
	isp_reg_clr(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CLEAR);

	hist->wait_acc_frames = conf->num_acc_frames;
}