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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  mtu; } ;
struct nes_vnic {scalar_t__ linkup; struct net_device* netdev; } ;
struct ib_port_attr {int lid; int port_cap_flags; int gid_tbl_len; int pkey_tbl_len; int max_msg_sz; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; void* state; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MTU_4096 ; 
 void* IB_PORT_ACTIVE ; 
 int IB_PORT_BOOT_MGMT_SUP ; 
 int IB_PORT_CM_SUP ; 
 void* IB_PORT_DOWN ; 
 int IB_PORT_REINIT_SUP ; 
 int IB_PORT_VENDOR_CLASS_SUP ; 
 int /*<<< orphan*/  IB_SPEED_SDR ; 
 int /*<<< orphan*/  IB_WIDTH_4X ; 
 int /*<<< orphan*/  ib_mtu_int_to_enum (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 struct nes_vnic* to_nesvnic (struct ib_device*) ; 

__attribute__((used)) static int nes_query_port(struct ib_device *ibdev, u8 port, struct ib_port_attr *props)
{
	struct nes_vnic *nesvnic = to_nesvnic(ibdev);
	struct net_device *netdev = nesvnic->netdev;

	/* props being zeroed by the caller, avoid zeroing it here */

	props->max_mtu = IB_MTU_4096;
	props->active_mtu = ib_mtu_int_to_enum(netdev->mtu);

	props->lid = 1;
	if (netif_queue_stopped(netdev))
		props->state = IB_PORT_DOWN;
	else if (nesvnic->linkup)
		props->state = IB_PORT_ACTIVE;
	else
		props->state = IB_PORT_DOWN;
	props->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_REINIT_SUP |
			IB_PORT_VENDOR_CLASS_SUP | IB_PORT_BOOT_MGMT_SUP;
	props->gid_tbl_len = 1;
	props->pkey_tbl_len = 1;
	props->active_width = IB_WIDTH_4X;
	props->active_speed = IB_SPEED_SDR;
	props->max_msg_sz = 0x80000000;

	return 0;
}