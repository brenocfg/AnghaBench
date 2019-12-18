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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int next2fill; } ;
struct TYPE_3__ {scalar_t__ base; } ;
struct vmxnet3_tx_queue {int txdata_desc_size; TYPE_2__ tx_ring; TYPE_1__ data_ring; } ;
struct vmxnet3_tx_ctx {int /*<<< orphan*/  copy_size; } ;
struct vmxnet3_adapter {int /*<<< orphan*/  netdev; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct Vmxnet3_TxDataDesc {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmxnet3_copy_hdr(struct sk_buff *skb, struct vmxnet3_tx_queue *tq,
		 struct vmxnet3_tx_ctx *ctx,
		 struct vmxnet3_adapter *adapter)
{
	struct Vmxnet3_TxDataDesc *tdd;

	tdd = (struct Vmxnet3_TxDataDesc *)((u8 *)tq->data_ring.base +
					    tq->tx_ring.next2fill *
					    tq->txdata_desc_size);

	memcpy(tdd->data, skb->data, ctx->copy_size);
	netdev_dbg(adapter->netdev,
		"copy %u bytes to dataRing[%u]\n",
		ctx->copy_size, tq->tx_ring.next2fill);
}