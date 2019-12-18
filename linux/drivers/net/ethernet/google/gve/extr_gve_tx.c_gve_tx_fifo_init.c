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
struct gve_tx_fifo {int size; scalar_t__ head; int /*<<< orphan*/  available; TYPE_1__* qpl; int /*<<< orphan*/  base; } ;
struct gve_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int num_entries; int /*<<< orphan*/  id; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MAP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gve_tx_fifo_init(struct gve_priv *priv, struct gve_tx_fifo *fifo)
{
	fifo->base = vmap(fifo->qpl->pages, fifo->qpl->num_entries, VM_MAP,
			  PAGE_KERNEL);
	if (unlikely(!fifo->base)) {
		netif_err(priv, drv, priv->dev, "Failed to vmap fifo, qpl_id = %d\n",
			  fifo->qpl->id);
		return -ENOMEM;
	}

	fifo->size = fifo->qpl->num_entries * PAGE_SIZE;
	atomic_set(&fifo->available, fifo->size);
	fifo->head = 0;
	return 0;
}