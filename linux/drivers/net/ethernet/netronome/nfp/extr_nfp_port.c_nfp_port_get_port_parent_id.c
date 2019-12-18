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
struct nfp_port {TYPE_1__* app; } ;
struct netdev_phys_item_id {int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_serial (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

int nfp_port_get_port_parent_id(struct net_device *netdev,
				struct netdev_phys_item_id *ppid)
{
	struct nfp_port *port;
	const u8 *serial;

	port = nfp_port_from_netdev(netdev);
	if (!port)
		return -EOPNOTSUPP;

	ppid->id_len = nfp_cpp_serial(port->app->cpp, &serial);
	memcpy(&ppid->id, serial, ppid->id_len);

	return 0;
}