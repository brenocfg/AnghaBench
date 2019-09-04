#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct crypto_platform_data {TYPE_1__* dma_slave; } ;
struct TYPE_5__ {int src_maxburst; int dst_maxburst; int device_fc; void* dst_addr_width; void* src_addr_width; scalar_t__ dst_addr; int /*<<< orphan*/  direction; } ;
struct TYPE_6__ {TYPE_2__ dma_conf; int /*<<< orphan*/  chan; } ;
struct atmel_sha_dev {TYPE_3__ dma_lch_in; scalar_t__ phys_base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_4__ {int /*<<< orphan*/  rxdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 void* DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int ENODEV ; 
 scalar_t__ SHA_REG_DIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_filter ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int atmel_sha_dma_init(struct atmel_sha_dev *dd,
				struct crypto_platform_data *pdata)
{
	dma_cap_mask_t mask_in;

	/* Try to grab DMA channel */
	dma_cap_zero(mask_in);
	dma_cap_set(DMA_SLAVE, mask_in);

	dd->dma_lch_in.chan = dma_request_slave_channel_compat(mask_in,
			atmel_sha_filter, &pdata->dma_slave->rxdata, dd->dev, "tx");
	if (!dd->dma_lch_in.chan) {
		dev_warn(dd->dev, "no DMA channel available\n");
		return -ENODEV;
	}

	dd->dma_lch_in.dma_conf.direction = DMA_MEM_TO_DEV;
	dd->dma_lch_in.dma_conf.dst_addr = dd->phys_base +
		SHA_REG_DIN(0);
	dd->dma_lch_in.dma_conf.src_maxburst = 1;
	dd->dma_lch_in.dma_conf.src_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_in.dma_conf.dst_maxburst = 1;
	dd->dma_lch_in.dma_conf.dst_addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dd->dma_lch_in.dma_conf.device_fc = false;

	return 0;
}