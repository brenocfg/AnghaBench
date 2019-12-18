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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct can_ctrlmode {int flags; int mask; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD ; 
 int EOPNOTSUPP ; 
 size_t IFLA_CAN_BITTIMING ; 
 size_t IFLA_CAN_CTRLMODE ; 
 size_t IFLA_CAN_DATA_BITTIMING ; 
 struct can_ctrlmode* nla_data (struct nlattr*) ; 

__attribute__((used)) static int can_validate(struct nlattr *tb[], struct nlattr *data[],
			struct netlink_ext_ack *extack)
{
	bool is_can_fd = false;

	/* Make sure that valid CAN FD configurations always consist of
	 * - nominal/arbitration bittiming
	 * - data bittiming
	 * - control mode with CAN_CTRLMODE_FD set
	 */

	if (!data)
		return 0;

	if (data[IFLA_CAN_CTRLMODE]) {
		struct can_ctrlmode *cm = nla_data(data[IFLA_CAN_CTRLMODE]);

		is_can_fd = cm->flags & cm->mask & CAN_CTRLMODE_FD;
	}

	if (is_can_fd) {
		if (!data[IFLA_CAN_BITTIMING] || !data[IFLA_CAN_DATA_BITTIMING])
			return -EOPNOTSUPP;
	}

	if (data[IFLA_CAN_DATA_BITTIMING]) {
		if (!is_can_fd || !data[IFLA_CAN_BITTIMING])
			return -EOPNOTSUPP;
	}

	return 0;
}