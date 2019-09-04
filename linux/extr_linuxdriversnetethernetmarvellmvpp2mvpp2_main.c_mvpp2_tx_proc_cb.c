#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct mvpp2_port_pcpu {int timer_scheduled; } ;
struct mvpp2_port {int ntxqs; int /*<<< orphan*/  pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvpp2_timer_set (struct mvpp2_port_pcpu*) ; 
 unsigned int mvpp2_tx_done (struct mvpp2_port*,unsigned int,int /*<<< orphan*/ ) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct mvpp2_port_pcpu* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_tx_proc_cb(unsigned long data)
{
	struct net_device *dev = (struct net_device *)data;
	struct mvpp2_port *port = netdev_priv(dev);
	struct mvpp2_port_pcpu *port_pcpu = this_cpu_ptr(port->pcpu);
	unsigned int tx_todo, cause;

	if (!netif_running(dev))
		return;
	port_pcpu->timer_scheduled = false;

	/* Process all the Tx queues */
	cause = (1 << port->ntxqs) - 1;
	tx_todo = mvpp2_tx_done(port, cause, smp_processor_id());

	/* Set the timer in case not all the packets were processed */
	if (tx_todo)
		mvpp2_timer_set(port_pcpu);
}