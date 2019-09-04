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
struct TYPE_2__ {int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_READY ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static int nicvf_check_pf_ready(struct nicvf *nic)
{
	union nic_mbx mbx = {};

	mbx.msg.msg = NIC_MBOX_MSG_READY;
	if (nicvf_send_msg_to_pf(nic, &mbx)) {
		netdev_err(nic->netdev,
			   "PF didn't respond to READY msg\n");
		return 0;
	}

	return 1;
}