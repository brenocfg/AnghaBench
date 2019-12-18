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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct gpmi_nand_data {struct dma_chan** dma_chans; int /*<<< orphan*/  dev; struct platform_device* pdev; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct dma_chan* dma_request_slave_channel (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  release_dma_channels (struct gpmi_nand_data*) ; 

__attribute__((used)) static int acquire_dma_channels(struct gpmi_nand_data *this)
{
	struct platform_device *pdev = this->pdev;
	struct dma_chan *dma_chan;

	/* request dma channel */
	dma_chan = dma_request_slave_channel(&pdev->dev, "rx-tx");
	if (!dma_chan) {
		dev_err(this->dev, "Failed to request DMA channel.\n");
		goto acquire_err;
	}

	this->dma_chans[0] = dma_chan;
	return 0;

acquire_err:
	release_dma_channels(this);
	return -EINVAL;
}