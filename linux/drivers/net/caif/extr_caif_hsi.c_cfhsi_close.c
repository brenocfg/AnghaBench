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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct cfhsi {TYPE_1__* ops; int /*<<< orphan*/ * rx_flip_buf; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  wq; int /*<<< orphan*/  aggregation_timer; int /*<<< orphan*/  rx_slowpath_timer; int /*<<< orphan*/  inactivity_timer; int /*<<< orphan*/  bits; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cfhsi_down ) (TYPE_1__*) ;int /*<<< orphan*/  (* cfhsi_rx_cancel ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CFHSI_SHUTDOWN ; 
 int /*<<< orphan*/  cfhsi_abort_tx (struct cfhsi*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct cfhsi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

__attribute__((used)) static int cfhsi_close(struct net_device *ndev)
{
	struct cfhsi *cfhsi = netdev_priv(ndev);
	u8 *tx_buf, *rx_buf, *flip_buf;

	/* going to shutdown driver */
	set_bit(CFHSI_SHUTDOWN, &cfhsi->bits);

	/* Delete timers if pending */
	del_timer_sync(&cfhsi->inactivity_timer);
	del_timer_sync(&cfhsi->rx_slowpath_timer);
	del_timer_sync(&cfhsi->aggregation_timer);

	/* Cancel pending RX request (if any) */
	cfhsi->ops->cfhsi_rx_cancel(cfhsi->ops);

	/* Destroy workqueue */
	destroy_workqueue(cfhsi->wq);

	/* Store bufferes: will be freed later. */
	tx_buf = cfhsi->tx_buf;
	rx_buf = cfhsi->rx_buf;
	flip_buf = cfhsi->rx_flip_buf;
	/* Flush transmit queues. */
	cfhsi_abort_tx(cfhsi);

	/* Deactivate interface */
	cfhsi->ops->cfhsi_down(cfhsi->ops);

	/* Free buffers. */
	kfree(tx_buf);
	kfree(rx_buf);
	kfree(flip_buf);
	return 0;
}