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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct cmdq_pkt {size_t buf_size; int /*<<< orphan*/  pa_base; struct cmdq_pkt* va_base; void* cl; } ;
struct cmdq_client {TYPE_2__* chan; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* mbox; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cmdq_pkt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,struct cmdq_pkt*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmdq_pkt*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

struct cmdq_pkt *cmdq_pkt_create(struct cmdq_client *client, size_t size)
{
	struct cmdq_pkt *pkt;
	struct device *dev;
	dma_addr_t dma_addr;

	pkt = kzalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return ERR_PTR(-ENOMEM);
	pkt->va_base = kzalloc(size, GFP_KERNEL);
	if (!pkt->va_base) {
		kfree(pkt);
		return ERR_PTR(-ENOMEM);
	}
	pkt->buf_size = size;
	pkt->cl = (void *)client;

	dev = client->chan->mbox->dev;
	dma_addr = dma_map_single(dev, pkt->va_base, pkt->buf_size,
				  DMA_TO_DEVICE);
	if (dma_mapping_error(dev, dma_addr)) {
		dev_err(dev, "dma map failed, size=%u\n", (u32)(u64)size);
		kfree(pkt->va_base);
		kfree(pkt);
		return ERR_PTR(-ENOMEM);
	}

	pkt->pa_base = dma_addr;

	return pkt;
}