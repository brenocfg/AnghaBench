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
struct net_device {int dummy; } ;
struct mvpp2_port_pcpu {int timer_scheduled; int /*<<< orphan*/  tx_done_timer; } ;
struct mvpp2_port {int /*<<< orphan*/  stats_work; int /*<<< orphan*/  pcpu; TYPE_1__* priv; int /*<<< orphan*/  has_tx_irqs; scalar_t__ link_irq; scalar_t__ phylink; } ;
struct TYPE_2__ {unsigned int nthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mvpp2_port*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp22_pcs_reset_assert (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_cleanup_rxqs (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_cleanup_txqs (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_interrupts_mask ; 
 int /*<<< orphan*/  mvpp2_irqs_deinit (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_mac_reset_assert (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_shared_interrupt_mask_unmask (struct mvpp2_port*,int) ; 
 int /*<<< orphan*/  mvpp2_stop_dev (struct mvpp2_port*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mvpp2_port*,int) ; 
 struct mvpp2_port_pcpu* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (scalar_t__) ; 

__attribute__((used)) static int mvpp2_stop(struct net_device *dev)
{
	struct mvpp2_port *port = netdev_priv(dev);
	struct mvpp2_port_pcpu *port_pcpu;
	unsigned int thread;

	mvpp2_stop_dev(port);

	/* Mask interrupts on all threads */
	on_each_cpu(mvpp2_interrupts_mask, port, 1);
	mvpp2_shared_interrupt_mask_unmask(port, true);

	if (port->phylink)
		phylink_disconnect_phy(port->phylink);
	if (port->link_irq)
		free_irq(port->link_irq, port);

	mvpp2_irqs_deinit(port);
	if (!port->has_tx_irqs) {
		for (thread = 0; thread < port->priv->nthreads; thread++) {
			port_pcpu = per_cpu_ptr(port->pcpu, thread);

			hrtimer_cancel(&port_pcpu->tx_done_timer);
			port_pcpu->timer_scheduled = false;
		}
	}
	mvpp2_cleanup_rxqs(port);
	mvpp2_cleanup_txqs(port);

	cancel_delayed_work_sync(&port->stats_work);

	mvpp2_mac_reset_assert(port);
	mvpp22_pcs_reset_assert(port);

	return 0;
}