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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_port {int /*<<< orphan*/  eth_id; int /*<<< orphan*/  dl_port; TYPE_1__* app; } ;
struct nfp_eth_table_port {int /*<<< orphan*/  label_subport; int /*<<< orphan*/  is_split; int /*<<< orphan*/  label_port; } ;
struct nfp_app {int /*<<< orphan*/  pf; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
 int /*<<< orphan*/  devlink_port_attrs_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int devlink_port_register (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfp_cpp_serial (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int nfp_devlink_fill_eth_port (struct nfp_port*,struct nfp_eth_table_port*) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int nfp_devlink_port_register(struct nfp_app *app, struct nfp_port *port)
{
	struct nfp_eth_table_port eth_port;
	struct devlink *devlink;
	const u8 *serial;
	int serial_len;
	int ret;

	rtnl_lock();
	ret = nfp_devlink_fill_eth_port(port, &eth_port);
	rtnl_unlock();
	if (ret)
		return ret;

	serial_len = nfp_cpp_serial(port->app->cpp, &serial);
	devlink_port_attrs_set(&port->dl_port, DEVLINK_PORT_FLAVOUR_PHYSICAL,
			       eth_port.label_port, eth_port.is_split,
			       eth_port.label_subport, serial, serial_len);

	devlink = priv_to_devlink(app->pf);

	return devlink_port_register(devlink, &port->dl_port, port->eth_id);
}