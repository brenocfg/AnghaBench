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
struct ehea_port {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ EHEA_PORT_DOWN ; 
 int /*<<< orphan*/  H_DEREG_BCMC ; 
 int /*<<< orphan*/  ehea_allmulti (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_broadcast_reg_helper (struct ehea_port*,int /*<<< orphan*/ ) ; 
 int ehea_clean_all_portres (struct ehea_port*) ; 
 int /*<<< orphan*/  ehea_drop_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  ehea_free_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  ehea_update_bcmc_registrations () ; 
 int /*<<< orphan*/  ehea_update_firmware_handles () ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ehea_down(struct net_device *dev)
{
	int ret;
	struct ehea_port *port = netdev_priv(dev);

	if (port->state == EHEA_PORT_DOWN)
		return 0;

	ehea_drop_multicast_list(dev);
	ehea_allmulti(dev, 0);
	ehea_broadcast_reg_helper(port, H_DEREG_BCMC);

	ehea_free_interrupts(dev);

	port->state = EHEA_PORT_DOWN;

	ehea_update_bcmc_registrations();

	ret = ehea_clean_all_portres(port);
	if (ret)
		netdev_info(dev, "Failed freeing resources. ret=%i\n", ret);

	ehea_update_firmware_handles();

	return ret;
}