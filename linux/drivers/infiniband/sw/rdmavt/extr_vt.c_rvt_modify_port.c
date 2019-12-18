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
struct rvt_ibport {scalar_t__ qkey_violations; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  port_cap3_flags; } ;
struct TYPE_2__ {int (* shut_down_port ) (struct rvt_dev_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cap_mask_chg ) (struct rvt_dev_info*,int /*<<< orphan*/ ) ;} ;
struct rvt_dev_info {TYPE_1__ driver_f; struct rvt_ibport** ports; } ;
struct ib_port_modify {int /*<<< orphan*/  clr_port_cap_mask; int /*<<< orphan*/  set_port_cap_mask; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_PORT_OPA_MASK_CHG ; 
 int IB_PORT_RESET_QKEY_CNTR ; 
 int IB_PORT_SHUTDOWN ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int ibport_num_to_idx (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rvt_dev_info*,int /*<<< orphan*/ ) ; 
 int stub2 (struct rvt_dev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvt_modify_port(struct ib_device *ibdev, u8 port_num,
			   int port_modify_mask, struct ib_port_modify *props)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	struct rvt_ibport *rvp;
	int ret = 0;
	int port_index = ibport_num_to_idx(ibdev, port_num);

	if (port_index < 0)
		return -EINVAL;

	rvp = rdi->ports[port_index];
	if (port_modify_mask & IB_PORT_OPA_MASK_CHG) {
		rvp->port_cap3_flags |= props->set_port_cap_mask;
		rvp->port_cap3_flags &= ~props->clr_port_cap_mask;
	} else {
		rvp->port_cap_flags |= props->set_port_cap_mask;
		rvp->port_cap_flags &= ~props->clr_port_cap_mask;
	}

	if (props->set_port_cap_mask || props->clr_port_cap_mask)
		rdi->driver_f.cap_mask_chg(rdi, port_num);
	if (port_modify_mask & IB_PORT_SHUTDOWN)
		ret = rdi->driver_f.shut_down_port(rdi, port_num);
	if (port_modify_mask & IB_PORT_RESET_QKEY_CNTR)
		rvp->qkey_violations = 0;

	return ret;
}