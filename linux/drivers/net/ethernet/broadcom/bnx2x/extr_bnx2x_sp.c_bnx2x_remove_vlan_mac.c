#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* put_credit ) (TYPE_3__*) ;int (* get_credit ) (TYPE_3__*) ;} ;
union bnx2x_qable_obj {TYPE_3__ vlan_mac; } ;
struct TYPE_5__ {int cmd; int /*<<< orphan*/  vlan_mac_flags; } ;
struct TYPE_6__ {TYPE_1__ vlan_mac; } ;
struct bnx2x_exeq_elem {TYPE_2__ cmd_data; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DONT_CONSUME_CAM_CREDIT ; 
#define  BNX2X_VLAN_MAC_ADD 130 
#define  BNX2X_VLAN_MAC_DEL 129 
#define  BNX2X_VLAN_MAC_MOVE 128 
 int EINVAL ; 
 int stub1 (TYPE_3__*) ; 
 int stub2 (TYPE_3__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_remove_vlan_mac(struct bnx2x *bp,
				  union bnx2x_qable_obj *qo,
				  struct bnx2x_exeq_elem *elem)
{
	int rc = 0;

	/* If consumption wasn't required, nothing to do */
	if (test_bit(BNX2X_DONT_CONSUME_CAM_CREDIT,
		     &elem->cmd_data.vlan_mac.vlan_mac_flags))
		return 0;

	switch (elem->cmd_data.vlan_mac.cmd) {
	case BNX2X_VLAN_MAC_ADD:
	case BNX2X_VLAN_MAC_MOVE:
		rc = qo->vlan_mac.put_credit(&qo->vlan_mac);
		break;
	case BNX2X_VLAN_MAC_DEL:
		rc = qo->vlan_mac.get_credit(&qo->vlan_mac);
		break;
	default:
		return -EINVAL;
	}

	if (rc != true)
		return -EINVAL;

	return 0;
}