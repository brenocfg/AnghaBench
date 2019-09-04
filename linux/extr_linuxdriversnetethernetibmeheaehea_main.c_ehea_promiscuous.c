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
typedef  scalar_t__ u64 ;
struct net_device {int dummy; } ;
struct hcp_ehea_port_cb7 {int /*<<< orphan*/  def_uc_qpn; } ;
struct ehea_port {int promisc; int /*<<< orphan*/  logical_port_id; TYPE_3__* adapter; TYPE_2__* port_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {TYPE_1__* qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  H_PORT_CB7 ; 
 int /*<<< orphan*/  H_PORT_CB7_DUCQPN ; 
 scalar_t__ ehea_h_modify_ehea_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hcp_ehea_port_cb7*) ; 
 int /*<<< orphan*/  ehea_promiscuous_error (scalar_t__,int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ehea_promiscuous(struct net_device *dev, int enable)
{
	struct ehea_port *port = netdev_priv(dev);
	struct hcp_ehea_port_cb7 *cb7;
	u64 hret;

	if (enable == port->promisc)
		return;

	cb7 = (void *)get_zeroed_page(GFP_ATOMIC);
	if (!cb7) {
		pr_err("no mem for cb7\n");
		goto out;
	}

	/* Modify Pxs_DUCQPN in CB7 */
	cb7->def_uc_qpn = enable == 1 ? port->port_res[0].qp->fw_handle : 0;

	hret = ehea_h_modify_ehea_port(port->adapter->handle,
				       port->logical_port_id,
				       H_PORT_CB7, H_PORT_CB7_DUCQPN, cb7);
	if (hret) {
		ehea_promiscuous_error(hret, enable);
		goto out;
	}

	port->promisc = enable;
out:
	free_page((unsigned long)cb7);
}