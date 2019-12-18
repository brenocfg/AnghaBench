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
struct port {int carrier; int /*<<< orphan*/  loopback; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct port* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  npe_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hss_hdlc_set_carrier(void *pdev, int carrier)
{
	struct net_device *netdev = pdev;
	struct port *port = dev_to_port(netdev);
	unsigned long flags;

	spin_lock_irqsave(&npe_lock, flags);
	port->carrier = carrier;
	if (!port->loopback) {
		if (carrier)
			netif_carrier_on(netdev);
		else
			netif_carrier_off(netdev);
	}
	spin_unlock_irqrestore(&npe_lock, flags);
}