#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct srp_target_port {int queue_size; int /*<<< orphan*/  srp_host; } ;
struct srp_rdma_ch {TYPE_1__** rx_ring; TYPE_1__** tx_ring; int /*<<< orphan*/  free_tx; int /*<<< orphan*/  max_it_iu_len; int /*<<< orphan*/  max_ti_iu_len; struct srp_target_port* target; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__**) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* srp_alloc_iu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_free_iu (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int srp_alloc_iu_bufs(struct srp_rdma_ch *ch)
{
	struct srp_target_port *target = ch->target;
	int i;

	ch->rx_ring = kcalloc(target->queue_size, sizeof(*ch->rx_ring),
			      GFP_KERNEL);
	if (!ch->rx_ring)
		goto err_no_ring;
	ch->tx_ring = kcalloc(target->queue_size, sizeof(*ch->tx_ring),
			      GFP_KERNEL);
	if (!ch->tx_ring)
		goto err_no_ring;

	for (i = 0; i < target->queue_size; ++i) {
		ch->rx_ring[i] = srp_alloc_iu(target->srp_host,
					      ch->max_ti_iu_len,
					      GFP_KERNEL, DMA_FROM_DEVICE);
		if (!ch->rx_ring[i])
			goto err;
	}

	for (i = 0; i < target->queue_size; ++i) {
		ch->tx_ring[i] = srp_alloc_iu(target->srp_host,
					      ch->max_it_iu_len,
					      GFP_KERNEL, DMA_TO_DEVICE);
		if (!ch->tx_ring[i])
			goto err;

		list_add(&ch->tx_ring[i]->list, &ch->free_tx);
	}

	return 0;

err:
	for (i = 0; i < target->queue_size; ++i) {
		srp_free_iu(target->srp_host, ch->rx_ring[i]);
		srp_free_iu(target->srp_host, ch->tx_ring[i]);
	}


err_no_ring:
	kfree(ch->tx_ring);
	ch->tx_ring = NULL;
	kfree(ch->rx_ring);
	ch->rx_ring = NULL;

	return -ENOMEM;
}