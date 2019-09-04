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
typedef  int /*<<< orphan*/  u32 ;
struct ispstat {int buf_size; struct isp_device* isp; TYPE_1__* active_buf; } ;
struct isp_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * virt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPHIST_ADDR ; 
 int /*<<< orphan*/  ISPHIST_CNT ; 
 int /*<<< orphan*/  ISPHIST_CNT_CLEAR ; 
 int /*<<< orphan*/  ISPHIST_DATA ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_HIST ; 
 int STAT_BUF_DONE ; 
 int STAT_NO_BUF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hist_reset_mem (struct ispstat*) ; 
 int /*<<< orphan*/  isp_reg_clr (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_buf_pio(struct ispstat *hist)
{
	struct isp_device *isp = hist->isp;
	u32 *buf = hist->active_buf->virt_addr;
	unsigned int i;

	if (!buf) {
		dev_dbg(isp->dev, "hist: invalid PIO buffer address\n");
		hist_reset_mem(hist);
		return STAT_NO_BUF;
	}

	isp_reg_writel(isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDR);

	/*
	 * By setting it, the histogram internal buffer is being cleared at the
	 * same time it's being read. This bit must be cleared just after all
	 * data is acquired.
	 */
	isp_reg_set(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CLEAR);

	/*
	 * We'll read 4 times a 4-bytes-word at each iteration for
	 * optimization. It avoids 3/4 of the jumps. We also know buf_size is
	 * divisible by 16.
	 */
	for (i = hist->buf_size / 16; i > 0; i--) {
		*buf++ = isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_reg_readl(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
	}
	isp_reg_clr(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CLEAR);

	return STAT_BUF_DONE;
}