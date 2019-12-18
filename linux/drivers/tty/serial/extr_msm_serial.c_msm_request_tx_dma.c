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
struct msm_dma {int device_fc; int /*<<< orphan*/  chan; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  dir; int /*<<< orphan*/  slave_id; int /*<<< orphan*/  dst_maxburst; scalar_t__ dst_addr; int /*<<< orphan*/  direction; } ;
struct TYPE_2__ {struct device* dev; } ;
struct msm_port {scalar_t__ is_uartdm; struct msm_dma tx_dma; TYPE_1__ uart; } ;
struct dma_slave_config {int device_fc; int /*<<< orphan*/  chan; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  dir; int /*<<< orphan*/  slave_id; int /*<<< orphan*/  dst_maxburst; scalar_t__ dst_addr; int /*<<< orphan*/  direction; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  scalar_t__ resource_size_t ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ UARTDM_1P4 ; 
 int /*<<< orphan*/  UARTDM_BURST_SIZE ; 
 int /*<<< orphan*/  UARTDM_DMEN_TX_BAM_ENABLE ; 
 int /*<<< orphan*/  UARTDM_DMEN_TX_DM_ENABLE ; 
 scalar_t__ UARTDM_TF ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel_reason (struct device*,char*) ; 
 int dmaengine_slave_config (int /*<<< orphan*/ ,struct msm_dma*) ; 
 int /*<<< orphan*/  memset (struct msm_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msm_request_tx_dma(struct msm_port *msm_port, resource_size_t base)
{
	struct device *dev = msm_port->uart.dev;
	struct dma_slave_config conf;
	struct msm_dma *dma;
	u32 crci = 0;
	int ret;

	dma = &msm_port->tx_dma;

	/* allocate DMA resources, if available */
	dma->chan = dma_request_slave_channel_reason(dev, "tx");
	if (IS_ERR(dma->chan))
		goto no_tx;

	of_property_read_u32(dev->of_node, "qcom,tx-crci", &crci);

	memset(&conf, 0, sizeof(conf));
	conf.direction = DMA_MEM_TO_DEV;
	conf.device_fc = true;
	conf.dst_addr = base + UARTDM_TF;
	conf.dst_maxburst = UARTDM_BURST_SIZE;
	conf.slave_id = crci;

	ret = dmaengine_slave_config(dma->chan, &conf);
	if (ret)
		goto rel_tx;

	dma->dir = DMA_TO_DEVICE;

	if (msm_port->is_uartdm < UARTDM_1P4)
		dma->enable_bit = UARTDM_DMEN_TX_DM_ENABLE;
	else
		dma->enable_bit = UARTDM_DMEN_TX_BAM_ENABLE;

	return;

rel_tx:
	dma_release_channel(dma->chan);
no_tx:
	memset(dma, 0, sizeof(*dma));
}