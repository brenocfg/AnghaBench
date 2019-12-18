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
struct siw_device {scalar_t__ state; TYPE_1__* netdev; } ;
struct ib_port_attr {int active_speed; int active_width; int gid_tbl_len; int max_msg_sz; int pkey_tbl_len; int port_cap_flags; scalar_t__ state; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  active_mtu; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 scalar_t__ IB_PORT_ACTIVE ; 
 int IB_PORT_CM_SUP ; 
 int IB_PORT_DEVICE_MGMT_SUP ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_DISABLED ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_LINK_UP ; 
 int /*<<< orphan*/  ib_mtu_int_to_enum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 struct siw_device* to_siw_dev (struct ib_device*) ; 

int siw_query_port(struct ib_device *base_dev, u8 port,
		   struct ib_port_attr *attr)
{
	struct siw_device *sdev = to_siw_dev(base_dev);

	memset(attr, 0, sizeof(*attr));

	attr->active_mtu = attr->max_mtu;
	attr->active_speed = 2;
	attr->active_width = 2;
	attr->gid_tbl_len = 1;
	attr->max_msg_sz = -1;
	attr->max_mtu = ib_mtu_int_to_enum(sdev->netdev->mtu);
	attr->phys_state = sdev->state == IB_PORT_ACTIVE ?
		IB_PORT_PHYS_STATE_LINK_UP : IB_PORT_PHYS_STATE_DISABLED;
	attr->pkey_tbl_len = 1;
	attr->port_cap_flags = IB_PORT_CM_SUP | IB_PORT_DEVICE_MGMT_SUP;
	attr->state = sdev->state;
	/*
	 * All zero
	 *
	 * attr->lid = 0;
	 * attr->bad_pkey_cntr = 0;
	 * attr->qkey_viol_cntr = 0;
	 * attr->sm_lid = 0;
	 * attr->lmc = 0;
	 * attr->max_vl_num = 0;
	 * attr->sm_sl = 0;
	 * attr->subnet_timeout = 0;
	 * attr->init_type_repy = 0;
	 */
	return 0;
}