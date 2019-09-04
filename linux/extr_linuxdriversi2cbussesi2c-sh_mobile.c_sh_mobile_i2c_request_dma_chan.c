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
struct dma_slave_config {int direction; void* src_addr_width; void* src_addr; void* dst_addr_width; void* dst_addr; } ;
struct dma_chan {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int DMA_MEM_TO_DEV ; 
 void* DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 struct dma_chan* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dma_chan*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  dma_release_channel (struct dma_chan*) ; 
 struct dma_chan* dma_request_slave_channel_reason (struct device*,char*) ; 
 int dmaengine_slave_config (struct dma_chan*,struct dma_slave_config*) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dma_chan *sh_mobile_i2c_request_dma_chan(struct device *dev,
				enum dma_transfer_direction dir, dma_addr_t port_addr)
{
	struct dma_chan *chan;
	struct dma_slave_config cfg;
	char *chan_name = dir == DMA_MEM_TO_DEV ? "tx" : "rx";
	int ret;

	chan = dma_request_slave_channel_reason(dev, chan_name);
	if (IS_ERR(chan)) {
		dev_dbg(dev, "request_channel failed for %s (%ld)\n", chan_name,
			PTR_ERR(chan));
		return chan;
	}

	memset(&cfg, 0, sizeof(cfg));
	cfg.direction = dir;
	if (dir == DMA_MEM_TO_DEV) {
		cfg.dst_addr = port_addr;
		cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	} else {
		cfg.src_addr = port_addr;
		cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	}

	ret = dmaengine_slave_config(chan, &cfg);
	if (ret) {
		dev_dbg(dev, "slave_config failed for %s (%d)\n", chan_name, ret);
		dma_release_channel(chan);
		return ERR_PTR(ret);
	}

	dev_dbg(dev, "got DMA channel for %s\n", chan_name);
	return chan;
}