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
struct omap3isp_hist_config {int dummy; } ;
struct ispstat {int /*<<< orphan*/ * dma_ch; int /*<<< orphan*/  event_type; struct omap3isp_hist_config* priv; int /*<<< orphan*/ * ops; struct isp_device* isp; } ;
struct isp_device {int /*<<< orphan*/  dev; struct ispstat isp_hist; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HIST_CONFIG_DMA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_EVENT_OMAP3ISP_HIST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct omap3isp_hist_config* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_request_chan_by_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hist_ops ; 
 int /*<<< orphan*/  hist_subdev_ops ; 
 int omap3isp_stat_init (struct ispstat*,char*,int /*<<< orphan*/ *) ; 

int omap3isp_hist_init(struct isp_device *isp)
{
	struct ispstat *hist = &isp->isp_hist;
	struct omap3isp_hist_config *hist_cfg;
	int ret = -1;

	hist_cfg = devm_kzalloc(isp->dev, sizeof(*hist_cfg), GFP_KERNEL);
	if (hist_cfg == NULL)
		return -ENOMEM;

	hist->isp = isp;

	if (HIST_CONFIG_DMA) {
		dma_cap_mask_t mask;

		/*
		 * We need slave capable channel without DMA request line for
		 * reading out the data.
		 * For this we can use dma_request_chan_by_mask() as we are
		 * happy with any channel as long as it is capable of slave
		 * configuration.
		 */
		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);
		hist->dma_ch = dma_request_chan_by_mask(&mask);
		if (IS_ERR(hist->dma_ch)) {
			ret = PTR_ERR(hist->dma_ch);
			if (ret == -EPROBE_DEFER)
				return ret;

			hist->dma_ch = NULL;
			dev_warn(isp->dev,
				 "hist: DMA channel request failed, using PIO\n");
		} else {
			dev_dbg(isp->dev, "hist: using DMA channel %s\n",
				dma_chan_name(hist->dma_ch));
		}
	}

	hist->ops = &hist_ops;
	hist->priv = hist_cfg;
	hist->event_type = V4L2_EVENT_OMAP3ISP_HIST;

	ret = omap3isp_stat_init(hist, "histogram", &hist_subdev_ops);
	if (ret) {
		if (hist->dma_ch)
			dma_release_channel(hist->dma_ch);
	}

	return ret;
}