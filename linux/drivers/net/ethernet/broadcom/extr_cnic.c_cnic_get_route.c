#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct in6_addr {int dummy; } ;
struct dst_entry {scalar_t__ dev; } ;
struct TYPE_11__ {scalar_t__ sin_family; int /*<<< orphan*/  sin_port; } ;
struct TYPE_8__ {scalar_t__ sin6_family; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_12__ {TYPE_4__ v4; TYPE_1__ v6; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_14__ {scalar_t__ sin_family; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct TYPE_13__ {scalar_t__ sin6_family; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_10__ {TYPE_7__ v4; TYPE_6__ v6; } ;
struct cnic_sockaddr {TYPE_5__ local; TYPE_3__ remote; } ;
struct cnic_sock {int /*<<< orphan*/  src_port; int /*<<< orphan*/  mtu; scalar_t__ vlan_id; int /*<<< orphan*/  dst_port; int /*<<< orphan*/ * dst_ip; int /*<<< orphan*/  flags; struct cnic_dev* dev; } ;
struct cnic_local {int /*<<< orphan*/  csk_port_tbl; } ;
struct cnic_dev {struct net_device* netdev; struct cnic_local* cnic_priv; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int CNIC_LOCAL_PORT_MAX ; 
 int CNIC_LOCAL_PORT_MIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SK_F_IPV6 ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cnic_alloc_id (int /*<<< orphan*/ *,int) ; 
 int cnic_alloc_new_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_get_v4_route (TYPE_7__*,struct dst_entry**) ; 
 int /*<<< orphan*/  cnic_get_v6_route (TYPE_6__*,struct dst_entry**) ; 
 scalar_t__ cnic_get_vlan (scalar_t__,struct net_device**) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_get_route(struct cnic_sock *csk, struct cnic_sockaddr *saddr)
{
	struct cnic_dev *dev = csk->dev;
	struct cnic_local *cp = dev->cnic_priv;
	int is_v6, rc = 0;
	struct dst_entry *dst = NULL;
	struct net_device *realdev;
	__be16 local_port;
	u32 port_id;

	if (saddr->local.v6.sin6_family == AF_INET6 &&
	    saddr->remote.v6.sin6_family == AF_INET6)
		is_v6 = 1;
	else if (saddr->local.v4.sin_family == AF_INET &&
		 saddr->remote.v4.sin_family == AF_INET)
		is_v6 = 0;
	else
		return -EINVAL;

	clear_bit(SK_F_IPV6, &csk->flags);

	if (is_v6) {
		set_bit(SK_F_IPV6, &csk->flags);
		cnic_get_v6_route(&saddr->remote.v6, &dst);

		memcpy(&csk->dst_ip[0], &saddr->remote.v6.sin6_addr,
		       sizeof(struct in6_addr));
		csk->dst_port = saddr->remote.v6.sin6_port;
		local_port = saddr->local.v6.sin6_port;

	} else {
		cnic_get_v4_route(&saddr->remote.v4, &dst);

		csk->dst_ip[0] = saddr->remote.v4.sin_addr.s_addr;
		csk->dst_port = saddr->remote.v4.sin_port;
		local_port = saddr->local.v4.sin_port;
	}

	csk->vlan_id = 0;
	csk->mtu = dev->netdev->mtu;
	if (dst && dst->dev) {
		u16 vlan = cnic_get_vlan(dst->dev, &realdev);
		if (realdev == dev->netdev) {
			csk->vlan_id = vlan;
			csk->mtu = dst_mtu(dst);
		}
	}

	port_id = be16_to_cpu(local_port);
	if (port_id >= CNIC_LOCAL_PORT_MIN &&
	    port_id < CNIC_LOCAL_PORT_MAX) {
		if (cnic_alloc_id(&cp->csk_port_tbl, port_id))
			port_id = 0;
	} else
		port_id = 0;

	if (!port_id) {
		port_id = cnic_alloc_new_id(&cp->csk_port_tbl);
		if (port_id == -1) {
			rc = -ENOMEM;
			goto err_out;
		}
		local_port = cpu_to_be16(port_id);
	}
	csk->src_port = local_port;

err_out:
	dst_release(dst);
	return rc;
}