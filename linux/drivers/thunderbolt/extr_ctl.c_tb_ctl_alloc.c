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
struct tb_nhi {TYPE_1__* pdev; } ;
struct tb_ctl {TYPE_3__** rx_packets; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  frame_pool; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  request_queue_lock; void* callback_data; int /*<<< orphan*/  callback; struct tb_nhi* nhi; } ;
typedef  int /*<<< orphan*/  event_cb ;
struct TYPE_5__ {int /*<<< orphan*/  callback; } ;
struct TYPE_6__ {TYPE_2__ frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RING_FLAG_NO_SUSPEND ; 
 int TB_CTL_RX_PKG_COUNT ; 
 int /*<<< orphan*/  TB_FRAME_SIZE ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct tb_ctl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_ctl_dbg (struct tb_ctl*,char*) ; 
 int /*<<< orphan*/  tb_ctl_free (struct tb_ctl*) ; 
 TYPE_3__* tb_ctl_pkg_alloc (struct tb_ctl*) ; 
 int /*<<< orphan*/  tb_ctl_rx_callback ; 
 int /*<<< orphan*/  tb_ring_alloc_rx (struct tb_nhi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_ring_alloc_tx (struct tb_nhi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct tb_ctl *tb_ctl_alloc(struct tb_nhi *nhi, event_cb cb, void *cb_data)
{
	int i;
	struct tb_ctl *ctl = kzalloc(sizeof(*ctl), GFP_KERNEL);
	if (!ctl)
		return NULL;
	ctl->nhi = nhi;
	ctl->callback = cb;
	ctl->callback_data = cb_data;

	mutex_init(&ctl->request_queue_lock);
	INIT_LIST_HEAD(&ctl->request_queue);
	ctl->frame_pool = dma_pool_create("thunderbolt_ctl", &nhi->pdev->dev,
					 TB_FRAME_SIZE, 4, 0);
	if (!ctl->frame_pool)
		goto err;

	ctl->tx = tb_ring_alloc_tx(nhi, 0, 10, RING_FLAG_NO_SUSPEND);
	if (!ctl->tx)
		goto err;

	ctl->rx = tb_ring_alloc_rx(nhi, 0, 10, RING_FLAG_NO_SUSPEND, 0xffff,
				0xffff, NULL, NULL);
	if (!ctl->rx)
		goto err;

	for (i = 0; i < TB_CTL_RX_PKG_COUNT; i++) {
		ctl->rx_packets[i] = tb_ctl_pkg_alloc(ctl);
		if (!ctl->rx_packets[i])
			goto err;
		ctl->rx_packets[i]->frame.callback = tb_ctl_rx_callback;
	}

	tb_ctl_dbg(ctl, "control channel created\n");
	return ctl;
err:
	tb_ctl_free(ctl);
	return NULL;
}