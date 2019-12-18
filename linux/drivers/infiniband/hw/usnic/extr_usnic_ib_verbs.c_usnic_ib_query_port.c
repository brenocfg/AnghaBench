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
struct usnic_ib_dev {int /*<<< orphan*/  usdev_lock; TYPE_1__* ufdev; } ;
struct ib_port_attr {int lmc; int gid_tbl_len; int pkey_tbl_len; int max_vl_num; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; scalar_t__ qkey_viol_cntr; scalar_t__ bad_pkey_cntr; scalar_t__ port_cap_flags; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; scalar_t__ sm_sl; scalar_t__ sm_lid; scalar_t__ lid; int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  inaddr; int /*<<< orphan*/  link_up; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  IB_PORT_INIT ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_DISABLED ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_LINK_UP ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING ; 
 scalar_t__ ib_get_eth_speed (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iboe_get_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usnic_ib_dev* to_usdev (struct ib_device*) ; 
 int /*<<< orphan*/  usnic_dbg (char*) ; 

int usnic_ib_query_port(struct ib_device *ibdev, u8 port,
				struct ib_port_attr *props)
{
	struct usnic_ib_dev *us_ibdev = to_usdev(ibdev);

	usnic_dbg("\n");

	if (ib_get_eth_speed(ibdev, port, &props->active_speed,
			     &props->active_width))
		return -EINVAL;

	/*
	 * usdev_lock is acquired after (and not before) ib_get_eth_speed call
	 * because acquiring rtnl_lock in ib_get_eth_speed, while holding
	 * usdev_lock could lead to a deadlock.
	 */
	mutex_lock(&us_ibdev->usdev_lock);
	/* props being zeroed by the caller, avoid zeroing it here */

	props->lid = 0;
	props->lmc = 1;
	props->sm_lid = 0;
	props->sm_sl = 0;

	if (!us_ibdev->ufdev->link_up) {
		props->state = IB_PORT_DOWN;
		props->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	} else if (!us_ibdev->ufdev->inaddr) {
		props->state = IB_PORT_INIT;
		props->phys_state =
			IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING;
	} else {
		props->state = IB_PORT_ACTIVE;
		props->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	}

	props->port_cap_flags = 0;
	props->gid_tbl_len = 1;
	props->pkey_tbl_len = 1;
	props->bad_pkey_cntr = 0;
	props->qkey_viol_cntr = 0;
	props->max_mtu = IB_MTU_4096;
	props->active_mtu = iboe_get_mtu(us_ibdev->ufdev->mtu);
	/* Userspace will adjust for hdrs */
	props->max_msg_sz = us_ibdev->ufdev->mtu;
	props->max_vl_num = 1;
	mutex_unlock(&us_ibdev->usdev_lock);

	return 0;
}