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
typedef  void* u32 ;
struct device {int dummy; } ;
struct be_queue_info {void* head; } ;
struct be_tx_obj {struct be_queue_info q; } ;
struct be_eth_wrb {int /*<<< orphan*/  frag_len; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_head_inc (struct be_queue_info*) ; 
 struct be_eth_wrb* queue_head_node (struct be_queue_info*) ; 
 int /*<<< orphan*/  unmap_tx_frag (struct device*,struct be_eth_wrb*,int) ; 

__attribute__((used)) static void be_xmit_restore(struct be_adapter *adapter,
			    struct be_tx_obj *txo, u32 head, bool map_single,
			    u32 copied)
{
	struct device *dev;
	struct be_eth_wrb *wrb;
	struct be_queue_info *txq = &txo->q;

	dev = &adapter->pdev->dev;
	txq->head = head;

	/* skip the first wrb (hdr); it's not mapped */
	queue_head_inc(txq);
	while (copied) {
		wrb = queue_head_node(txq);
		unmap_tx_frag(dev, wrb, map_single);
		map_single = false;
		copied -= le32_to_cpu(wrb->frag_len);
		queue_head_inc(txq);
	}

	txq->head = head;
}