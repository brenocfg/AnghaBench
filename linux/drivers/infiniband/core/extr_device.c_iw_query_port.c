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
struct net_device {int /*<<< orphan*/  mtu; } ;
struct in_device {scalar_t__ ifa_list; } ;
struct ib_port_attr {int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; } ;
struct TYPE_2__ {int (* query_port ) (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ;} ;
struct ib_device {TYPE_1__ ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  IB_PORT_INIT ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_DISABLED ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_LINK_UP ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* ib_device_get_netdev (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mtu_int_to_enum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

__attribute__((used)) static int iw_query_port(struct ib_device *device,
			   u8 port_num,
			   struct ib_port_attr *port_attr)
{
	struct in_device *inetdev;
	struct net_device *netdev;
	int err;

	memset(port_attr, 0, sizeof(*port_attr));

	netdev = ib_device_get_netdev(device, port_num);
	if (!netdev)
		return -ENODEV;

	port_attr->max_mtu = IB_MTU_4096;
	port_attr->active_mtu = ib_mtu_int_to_enum(netdev->mtu);

	if (!netif_carrier_ok(netdev)) {
		port_attr->state = IB_PORT_DOWN;
		port_attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	} else {
		rcu_read_lock();
		inetdev = __in_dev_get_rcu(netdev);

		if (inetdev && inetdev->ifa_list) {
			port_attr->state = IB_PORT_ACTIVE;
			port_attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
		} else {
			port_attr->state = IB_PORT_INIT;
			port_attr->phys_state =
				IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING;
		}

		rcu_read_unlock();
	}

	dev_put(netdev);
	err = device->ops.query_port(device, port_num, port_attr);
	if (err)
		return err;

	return 0;
}