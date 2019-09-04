#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cmd; } ;
struct bnx2x_vlan_mac_ramrod_params {TYPE_2__ user_req; int /*<<< orphan*/  ramrod_flags; struct bnx2x_vlan_mac_obj* vlan_mac_obj; } ;
struct bnx2x_vlan_mac_obj {int /*<<< orphan*/  exe_queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  vlan_mac; } ;
struct bnx2x_exeq_elem {int cmd_len; TYPE_1__ cmd_data; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
#define  BNX2X_VLAN_MAC_MOVE 128 
 int ENOMEM ; 
 int /*<<< orphan*/  RAMROD_RESTORE ; 
 int bnx2x_exe_queue_add (struct bnx2x*,int /*<<< orphan*/ *,struct bnx2x_exeq_elem*,int) ; 
 struct bnx2x_exeq_elem* bnx2x_exe_queue_alloc_elem (struct bnx2x*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bnx2x_vlan_mac_push_new_cmd(
	struct bnx2x *bp,
	struct bnx2x_vlan_mac_ramrod_params *p)
{
	struct bnx2x_exeq_elem *elem;
	struct bnx2x_vlan_mac_obj *o = p->vlan_mac_obj;
	bool restore = test_bit(RAMROD_RESTORE, &p->ramrod_flags);

	/* Allocate the execution queue element */
	elem = bnx2x_exe_queue_alloc_elem(bp);
	if (!elem)
		return -ENOMEM;

	/* Set the command 'length' */
	switch (p->user_req.cmd) {
	case BNX2X_VLAN_MAC_MOVE:
		elem->cmd_len = 2;
		break;
	default:
		elem->cmd_len = 1;
	}

	/* Fill the object specific info */
	memcpy(&elem->cmd_data.vlan_mac, &p->user_req, sizeof(p->user_req));

	/* Try to add a new command to the pending list */
	return bnx2x_exe_queue_add(bp, &o->exe_queue, elem, restore);
}