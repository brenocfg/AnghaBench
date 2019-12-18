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
struct TYPE_3__ {scalar_t__ console; } ;
struct fwtty_port {int /*<<< orphan*/  con_data; TYPE_2__* fwcon_ops; TYPE_1__ port; int /*<<< orphan*/  lock; int /*<<< orphan*/  peer; int /*<<< orphan*/  max_payload; int /*<<< orphan*/  tx_fifo; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* notify ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FWCON_NOTIFY_DETACH ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCODE_100 ; 
 int /*<<< orphan*/  dma_fifo_change_tx_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtty_update_port_status (struct fwtty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_speed_to_max_payload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwserial_release_port(struct fwtty_port *port, bool reset)
{
	/* drop carrier (and all other line status) */
	if (reset)
		fwtty_update_port_status(port, 0);

	spin_lock_bh(&port->lock);

	/* reset dma fifo max transmission size back to S100 */
	port->max_payload = link_speed_to_max_payload(SCODE_100);
	dma_fifo_change_tx_limit(&port->tx_fifo, port->max_payload);

	RCU_INIT_POINTER(port->peer, NULL);
	spin_unlock_bh(&port->lock);

	if (port->port.console && port->fwcon_ops->notify)
		(*port->fwcon_ops->notify)(FWCON_NOTIFY_DETACH, port->con_data);
}