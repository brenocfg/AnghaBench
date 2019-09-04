#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct in_device {scalar_t__ ifa_list; } ;
struct ib_port_attr {int port_cap_flags; int gid_tbl_len; int pkey_tbl_len; int active_width; int max_msg_sz; int /*<<< orphan*/  active_speed; void* state; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {struct net_device** ports; } ;
struct TYPE_4__ {TYPE_1__ lldi; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MTU_4096 ; 
 void* IB_PORT_ACTIVE ; 
 int IB_PORT_BOOT_MGMT_SUP ; 
 int IB_PORT_CM_SUP ; 
 int IB_PORT_DEVICE_MGMT_SUP ; 
 void* IB_PORT_DOWN ; 
 void* IB_PORT_INIT ; 
 int IB_PORT_REINIT_SUP ; 
 int IB_PORT_SNMP_TUNNEL_SUP ; 
 int IB_PORT_VENDOR_CLASS_SUP ; 
 int /*<<< orphan*/  IB_SPEED_DDR ; 
 int /*<<< orphan*/  ib_mtu_int_to_enum (int /*<<< orphan*/ ) ; 
 struct in_device* in_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in_dev_put (struct in_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_device*) ; 
 struct c4iw_dev* to_c4iw_dev (struct ib_device*) ; 

__attribute__((used)) static int c4iw_query_port(struct ib_device *ibdev, u8 port,
			   struct ib_port_attr *props)
{
	struct c4iw_dev *dev;
	struct net_device *netdev;
	struct in_device *inetdev;

	pr_debug("ibdev %p\n", ibdev);

	dev = to_c4iw_dev(ibdev);
	netdev = dev->rdev.lldi.ports[port-1];
	/* props being zeroed by the caller, avoid zeroing it here */
	props->max_mtu = IB_MTU_4096;
	props->active_mtu = ib_mtu_int_to_enum(netdev->mtu);

	if (!netif_carrier_ok(netdev))
		props->state = IB_PORT_DOWN;
	else {
		inetdev = in_dev_get(netdev);
		if (inetdev) {
			if (inetdev->ifa_list)
				props->state = IB_PORT_ACTIVE;
			else
				props->state = IB_PORT_INIT;
			in_dev_put(inetdev);
		} else
			props->state = IB_PORT_INIT;
	}

	props->port_cap_flags =
	    IB_PORT_CM_SUP |
	    IB_PORT_SNMP_TUNNEL_SUP |
	    IB_PORT_REINIT_SUP |
	    IB_PORT_DEVICE_MGMT_SUP |
	    IB_PORT_VENDOR_CLASS_SUP | IB_PORT_BOOT_MGMT_SUP;
	props->gid_tbl_len = 1;
	props->pkey_tbl_len = 1;
	props->active_width = 2;
	props->active_speed = IB_SPEED_DDR;
	props->max_msg_sz = -1;

	return 0;
}