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
struct ehea_port {scalar_t__ state; int num_def_qps; TYPE_1__* port_res; int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 scalar_t__ EHEA_PORT_UP ; 
 int EIO ; 
 int /*<<< orphan*/  H_REG_BCMC ; 
 int ehea_activate_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ehea_broadcast_reg_helper (struct ehea_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_clean_all_portres (struct ehea_port*) ; 
 int ehea_configure_port (struct ehea_port*) ; 
 int ehea_fill_port_res (TYPE_1__*) ; 
 int /*<<< orphan*/  ehea_free_interrupts (struct net_device*) ; 
 int ehea_port_res_setup (struct ehea_port*,int) ; 
 int ehea_reg_interrupts (struct net_device*) ; 
 int /*<<< orphan*/  ehea_update_bcmc_registrations () ; 
 int /*<<< orphan*/  ehea_update_firmware_handles () ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ehea_up(struct net_device *dev)
{
	int ret, i;
	struct ehea_port *port = netdev_priv(dev);

	if (port->state == EHEA_PORT_UP)
		return 0;

	ret = ehea_port_res_setup(port, port->num_def_qps);
	if (ret) {
		netdev_err(dev, "port_res_failed\n");
		goto out;
	}

	/* Set default QP for this port */
	ret = ehea_configure_port(port);
	if (ret) {
		netdev_err(dev, "ehea_configure_port failed. ret:%d\n", ret);
		goto out_clean_pr;
	}

	ret = ehea_reg_interrupts(dev);
	if (ret) {
		netdev_err(dev, "reg_interrupts failed. ret:%d\n", ret);
		goto out_clean_pr;
	}

	for (i = 0; i < port->num_def_qps; i++) {
		ret = ehea_activate_qp(port->adapter, port->port_res[i].qp);
		if (ret) {
			netdev_err(dev, "activate_qp failed\n");
			goto out_free_irqs;
		}
	}

	for (i = 0; i < port->num_def_qps; i++) {
		ret = ehea_fill_port_res(&port->port_res[i]);
		if (ret) {
			netdev_err(dev, "out_free_irqs\n");
			goto out_free_irqs;
		}
	}

	ret = ehea_broadcast_reg_helper(port, H_REG_BCMC);
	if (ret) {
		ret = -EIO;
		goto out_free_irqs;
	}

	port->state = EHEA_PORT_UP;

	ret = 0;
	goto out;

out_free_irqs:
	ehea_free_interrupts(dev);

out_clean_pr:
	ehea_clean_all_portres(port);
out:
	if (ret)
		netdev_info(dev, "Failed starting. ret=%i\n", ret);

	ehea_update_bcmc_registrations();
	ehea_update_firmware_handles();

	return ret;
}