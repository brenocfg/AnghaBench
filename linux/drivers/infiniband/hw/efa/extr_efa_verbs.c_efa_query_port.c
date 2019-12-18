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
struct ib_port_attr {int lmc; int gid_tbl_len; int pkey_tbl_len; int max_vl_num; int /*<<< orphan*/  max_msg_sz; void* active_mtu; void* max_mtu; int /*<<< orphan*/  active_width; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  state; } ;
struct ib_device {int dummy; } ;
struct efa_dev {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_PORT_PHYS_STATE_LINK_UP ; 
 int /*<<< orphan*/  IB_SPEED_EDR ; 
 int /*<<< orphan*/  IB_WIDTH_4X ; 
 void* ib_mtu_int_to_enum (int /*<<< orphan*/ ) ; 
 struct efa_dev* to_edev (struct ib_device*) ; 

int efa_query_port(struct ib_device *ibdev, u8 port,
		   struct ib_port_attr *props)
{
	struct efa_dev *dev = to_edev(ibdev);

	props->lmc = 1;

	props->state = IB_PORT_ACTIVE;
	props->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	props->gid_tbl_len = 1;
	props->pkey_tbl_len = 1;
	props->active_speed = IB_SPEED_EDR;
	props->active_width = IB_WIDTH_4X;
	props->max_mtu = ib_mtu_int_to_enum(dev->mtu);
	props->active_mtu = ib_mtu_int_to_enum(dev->mtu);
	props->max_msg_sz = dev->mtu;
	props->max_vl_num = 1;

	return 0;
}