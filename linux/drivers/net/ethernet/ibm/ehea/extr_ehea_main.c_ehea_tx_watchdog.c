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
struct ehea_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __EHEA_STOP_XFER ; 
 int /*<<< orphan*/  ehea_driver_flags ; 
 int /*<<< orphan*/  ehea_schedule_port_reset (struct ehea_port*) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehea_tx_watchdog(struct net_device *dev)
{
	struct ehea_port *port = netdev_priv(dev);

	if (netif_carrier_ok(dev) &&
	    !test_bit(__EHEA_STOP_XFER, &ehea_driver_flags))
		ehea_schedule_port_reset(port);
}