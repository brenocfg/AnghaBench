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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_2__ ppid; } ;
struct switchdev_attr {int id; TYPE_3__ u; } ;
struct nfp_port {TYPE_1__* app; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_cpp_serial (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 struct nfp_port* nfp_port_from_netdev (struct net_device*) ; 

__attribute__((used)) static int
nfp_port_attr_get(struct net_device *netdev, struct switchdev_attr *attr)
{
	struct nfp_port *port;

	port = nfp_port_from_netdev(netdev);
	if (!port)
		return -EOPNOTSUPP;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID: {
		const u8 *serial;
		/* N.B: attr->u.ppid.id is binary data */
		attr->u.ppid.id_len = nfp_cpp_serial(port->app->cpp, &serial);
		memcpy(&attr->u.ppid.id, serial, attr->u.ppid.id_len);
		break;
	}
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}