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
struct rvt_ibport {int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  qkey_violations; int /*<<< orphan*/  pkey_violations; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; } ;
struct TYPE_2__ {int (* query_port_state ) (struct rvt_dev_info*,int /*<<< orphan*/ ,struct ib_port_attr*) ;} ;
struct rvt_dev_info {TYPE_1__ driver_f; struct rvt_ibport** ports; } ;
struct ib_port_attr {int max_msg_sz; scalar_t__ init_type_reply; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int ibport_num_to_idx (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_get_npkeys (struct rvt_dev_info*) ; 
 int stub1 (struct rvt_dev_info*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

__attribute__((used)) static int rvt_query_port(struct ib_device *ibdev, u8 port_num,
			  struct ib_port_attr *props)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	struct rvt_ibport *rvp;
	int port_index = ibport_num_to_idx(ibdev, port_num);

	if (port_index < 0)
		return -EINVAL;

	rvp = rdi->ports[port_index];
	/* props being zeroed by the caller, avoid zeroing it here */
	props->sm_lid = rvp->sm_lid;
	props->sm_sl = rvp->sm_sl;
	props->port_cap_flags = rvp->port_cap_flags;
	props->max_msg_sz = 0x80000000;
	props->pkey_tbl_len = rvt_get_npkeys(rdi);
	props->bad_pkey_cntr = rvp->pkey_violations;
	props->qkey_viol_cntr = rvp->qkey_violations;
	props->subnet_timeout = rvp->subnet_timeout;
	props->init_type_reply = 0;

	/* Populate the remaining ib_port_attr elements */
	return rdi->driver_f.query_port_state(rdi, port_num, props);
}