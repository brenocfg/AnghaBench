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
struct TYPE_2__ {int /*<<< orphan*/  drop_total; int /*<<< orphan*/  drop_fcs; int /*<<< orphan*/  drop_err; } ;
struct vmxnet3_rx_queue {TYPE_1__ stats; } ;
struct vmxnet3_rx_ctx {int /*<<< orphan*/ * skb; } ;
struct vmxnet3_adapter {int dummy; } ;
struct Vmxnet3_RxCompDesc {int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmxnet3_rx_error(struct vmxnet3_rx_queue *rq, struct Vmxnet3_RxCompDesc *rcd,
		 struct vmxnet3_rx_ctx *ctx,  struct vmxnet3_adapter *adapter)
{
	rq->stats.drop_err++;
	if (!rcd->fcs)
		rq->stats.drop_fcs++;

	rq->stats.drop_total++;

	/*
	 * We do not unmap and chain the rx buffer to the skb.
	 * We basically pretend this buffer is not used and will be recycled
	 * by vmxnet3_rq_alloc_rx_buf()
	 */

	/*
	 * ctx->skb may be NULL if this is the first and the only one
	 * desc for the pkt
	 */
	if (ctx->skb)
		dev_kfree_skb_irq(ctx->skb);

	ctx->skb = NULL;
}