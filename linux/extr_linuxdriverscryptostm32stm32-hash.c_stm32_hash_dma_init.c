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
struct stm32_hash_dev {int /*<<< orphan*/  dma_completion; int /*<<< orphan*/  dev; int /*<<< orphan*/ * dma_lch; int /*<<< orphan*/  dma_maxburst; scalar_t__ phys_base; } ;
struct dma_slave_config {int device_fc; int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  dst_addr_width; scalar_t__ dst_addr; int /*<<< orphan*/  direction; } ;
typedef  int /*<<< orphan*/  dma_conf ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int EBUSY ; 
 scalar_t__ HASH_DIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_request_slave_channel (int /*<<< orphan*/ ,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ *,struct dma_slave_config*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_hash_dma_init(struct stm32_hash_dev *hdev)
{
	struct dma_slave_config dma_conf;
	int err;

	memset(&dma_conf, 0, sizeof(dma_conf));

	dma_conf.direction = DMA_MEM_TO_DEV;
	dma_conf.dst_addr = hdev->phys_base + HASH_DIN;
	dma_conf.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	dma_conf.src_maxburst = hdev->dma_maxburst;
	dma_conf.dst_maxburst = hdev->dma_maxburst;
	dma_conf.device_fc = false;

	hdev->dma_lch = dma_request_slave_channel(hdev->dev, "in");
	if (!hdev->dma_lch) {
		dev_err(hdev->dev, "Couldn't acquire a slave DMA channel.\n");
		return -EBUSY;
	}

	err = dmaengine_slave_config(hdev->dma_lch, &dma_conf);
	if (err) {
		dma_release_channel(hdev->dma_lch);
		hdev->dma_lch = NULL;
		dev_err(hdev->dev, "Couldn't configure DMA slave.\n");
		return err;
	}

	init_completion(&hdev->dma_completion);

	return 0;
}