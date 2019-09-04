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
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct imx_i2c_struct {struct imx_i2c_dma* dma; TYPE_2__* hwdata; TYPE_1__ adapter; } ;
struct imx_i2c_dma {void* chan_tx; void* chan_rx; int /*<<< orphan*/  cmd_complete; } ;
struct dma_slave_config {int dst_maxburst; int src_maxburst; int /*<<< orphan*/  direction; void* src_addr_width; void* src_addr; void* dst_addr_width; void* dst_addr; } ;
typedef  void* dma_addr_t ;
struct TYPE_4__ {int regshift; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 void* DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMX_I2C_I2DR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct imx_i2c_dma*) ; 
 struct imx_i2c_dma* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_chan_name (void*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_slave_channel (struct device*,char*) ; 
 int dmaengine_slave_config (void*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2c_imx_dma_request(struct imx_i2c_struct *i2c_imx,
						dma_addr_t phy_addr)
{
	struct imx_i2c_dma *dma;
	struct dma_slave_config dma_sconfig;
	struct device *dev = &i2c_imx->adapter.dev;
	int ret;

	dma = devm_kzalloc(dev, sizeof(*dma), GFP_KERNEL);
	if (!dma)
		return;

	dma->chan_tx = dma_request_slave_channel(dev, "tx");
	if (!dma->chan_tx) {
		dev_dbg(dev, "can't request DMA tx channel\n");
		goto fail_al;
	}

	dma_sconfig.dst_addr = phy_addr +
				(IMX_I2C_I2DR << i2c_imx->hwdata->regshift);
	dma_sconfig.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.dst_maxburst = 1;
	dma_sconfig.direction = DMA_MEM_TO_DEV;
	ret = dmaengine_slave_config(dma->chan_tx, &dma_sconfig);
	if (ret < 0) {
		dev_dbg(dev, "can't configure tx channel\n");
		goto fail_tx;
	}

	dma->chan_rx = dma_request_slave_channel(dev, "rx");
	if (!dma->chan_rx) {
		dev_dbg(dev, "can't request DMA rx channel\n");
		goto fail_tx;
	}

	dma_sconfig.src_addr = phy_addr +
				(IMX_I2C_I2DR << i2c_imx->hwdata->regshift);
	dma_sconfig.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.src_maxburst = 1;
	dma_sconfig.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(dma->chan_rx, &dma_sconfig);
	if (ret < 0) {
		dev_dbg(dev, "can't configure rx channel\n");
		goto fail_rx;
	}

	i2c_imx->dma = dma;
	init_completion(&dma->cmd_complete);
	dev_info(dev, "using %s (tx) and %s (rx) for DMA transfers\n",
		dma_chan_name(dma->chan_tx), dma_chan_name(dma->chan_rx));

	return;

fail_rx:
	dma_release_channel(dma->chan_rx);
fail_tx:
	dma_release_channel(dma->chan_tx);
fail_al:
	devm_kfree(dev, dma);
	dev_info(dev, "can't use DMA, using PIO instead.\n");
}