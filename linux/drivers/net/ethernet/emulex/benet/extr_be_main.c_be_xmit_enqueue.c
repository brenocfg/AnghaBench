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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; scalar_t__ data_len; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct be_wrb_params {int dummy; } ;
struct be_tx_obj {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_map_errors; } ;
struct be_adapter {TYPE_2__ drv_stats; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int be_tx_get_wrb_hdr (struct be_tx_obj*) ; 
 int /*<<< orphan*/  be_tx_setup_wrb_frag (struct be_tx_obj*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_tx_setup_wrb_hdr (struct be_adapter*,struct be_tx_obj*,struct be_wrb_params*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  be_tx_stats_update (struct be_tx_obj*,struct sk_buff*) ; 
 int /*<<< orphan*/  be_xmit_restore (struct be_adapter*,struct be_tx_obj*,int,int,int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (struct device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/  const*) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int skb_wrb_cnt (struct sk_buff*) ; 

__attribute__((used)) static u32 be_xmit_enqueue(struct be_adapter *adapter, struct be_tx_obj *txo,
			   struct sk_buff *skb,
			   struct be_wrb_params *wrb_params)
{
	u32 i, copied = 0, wrb_cnt = skb_wrb_cnt(skb);
	struct device *dev = &adapter->pdev->dev;
	bool map_single = false;
	u32 head;
	dma_addr_t busaddr;
	int len;

	head = be_tx_get_wrb_hdr(txo);

	if (skb->len > skb->data_len) {
		len = skb_headlen(skb);

		busaddr = dma_map_single(dev, skb->data, len, DMA_TO_DEVICE);
		if (dma_mapping_error(dev, busaddr))
			goto dma_err;
		map_single = true;
		be_tx_setup_wrb_frag(txo, busaddr, len);
		copied += len;
	}

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		len = skb_frag_size(frag);

		busaddr = skb_frag_dma_map(dev, frag, 0, len, DMA_TO_DEVICE);
		if (dma_mapping_error(dev, busaddr))
			goto dma_err;
		be_tx_setup_wrb_frag(txo, busaddr, len);
		copied += len;
	}

	be_tx_setup_wrb_hdr(adapter, txo, wrb_params, skb, head);

	be_tx_stats_update(txo, skb);
	return wrb_cnt;

dma_err:
	adapter->drv_stats.dma_map_errors++;
	be_xmit_restore(adapter, txo, head, map_single, copied);
	return 0;
}